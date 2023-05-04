#pragma once
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    sf::Clock clock;
    ParticleSystem(unsigned int count) :
        m_particles(count),
        m_vertices(sf::Quads, count * 4),
        m_lifetime(sf::seconds(3.f)),
        m_emitter(0.f, 0.f)
    {
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // if the particle is dead, respawn it
            if (p.lifetime <= sf::Time::Zero)
            {
                resetParticle(i);
            }
            // update the position and color of the corresponding vertex
            m_vertices[i * 4].position += p.velocity * elapsed.asSeconds();
            m_vertices[i * 4 + 1].position = m_vertices[i * 4].position + sf::Vector2f(0, 1);
            m_vertices[i * 4 + 2].position = m_vertices[i * 4].position + sf::Vector2f(1, 1);
            m_vertices[i * 4 + 3].position = m_vertices[i * 4].position + sf::Vector2f(1, 0);

            m_vertices[i * 4].color = sf::Color(0, 0, 0, 255);
            m_vertices[i * 4 + 1].color = sf::Color(44, 0, 10, 255);
            m_vertices[i * 4 + 2].color = sf::Color(112, 44, 0, 255);
            m_vertices[i * 4 + 3].color = sf::Color(25, 5, 0, 255);

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i * 4].color.a = static_cast<sf::Uint8>(ratio * 255);
            m_vertices[i * 4 + 1].color.a = static_cast<sf::Uint8>(ratio * 255);
            m_vertices[i * 4 + 2].color.a = static_cast<sf::Uint8>(ratio * 255);
            m_vertices[i * 4 + 3].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = 50.f;
        sf::Time life{ sf::milliseconds((std::rand() % 2000) + 1000) };
        sf::Vector2f groupVel(sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed));
        m_particles[index].velocity = groupVel;
        m_particles[index].lifetime = life;

        // reset the position of the corresponding vertex
        m_vertices[index * 4].position = m_emitter;
        m_vertices[index * 4 + 1].position = m_emitter + sf::Vector2f(0, 1);
        m_vertices[index * 4 + 2].position = m_emitter + sf::Vector2f(1, 1);
        m_vertices[index * 4 + 3].position = m_emitter + sf::Vector2f(1, 0);
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};