#pragma once
#include <SFML/Graphics.hpp>
#include "flow.h"


class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    sf::Clock clock;
    // Construct the particle system with the number of particles per given lifetime
    ParticleSystem(unsigned int count, Flow &flow) :
        m_particles(count),
        m_vertices(sf::Quads, count * 4),
        m_lifetime(sf::seconds(15.f)),
        m_emitter(500, 500)
    {
        topLeft = sf::Color::White;
        topRight = sf::Color::White;
        bottomLeft = sf::Color::White;
        bottomRight = sf::Color::White;
        //m_flow = flow;
    }

    void setColor(sf::Color tL, sf::Color tR, sf::Color bR, sf::Color bL)
    {
        topLeft = tL;
        topRight = tR;
        bottomRight = bR;
        bottomLeft = bL;
    }
    inline void setColor(sf::Color tL) { setColor(tL, tL, tL, tL); }

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


            // get particle position. find out what square it's in. apply angle.
            sf::Vector2f particlePos = m_vertices[i * 4 + 0].position;
            const int gridX = particlePos.x / m_flow.tileSize.x;
            const int gridY = particlePos.y / m_flow.tileSize.y;
            float angle = m_flow.angleVector[gridX + gridY * (m_flow.width / m_flow.tileSize.x)];
            //float angle = 0;
            float speed = 200.f;
            sf::Vector2f groupVel(sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed));
            p.velocity = groupVel;




            m_vertices[i * 4 + 0].position += p.velocity * elapsed.asSeconds();
            m_vertices[i * 4 + 1].position = m_vertices[i * 4].position + sf::Vector2f(0, 1);
            m_vertices[i * 4 + 2].position = m_vertices[i * 4].position + sf::Vector2f(1, 1);
            m_vertices[i * 4 + 3].position = m_vertices[i * 4].position + sf::Vector2f(1, 0);

            m_vertices[i * 4 + 0].color = topLeft;
            m_vertices[i * 4 + 1].color = topRight;
            m_vertices[i * 4 + 2].color = bottomRight;
            m_vertices[i * 4 + 3].color = bottomLeft;

            // update the alpha (transparency) of the particle according to its lifetime
            //float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            //m_vertices[i * 4 + 0].color.a = static_cast<sf::Uint8>(ratio * 255);
            //m_vertices[i * 4 + 1].color.a = static_cast<sf::Uint8>(ratio * 255);
            //m_vertices[i * 4 + 2].color.a = static_cast<sf::Uint8>(ratio * 255);
            //m_vertices[i * 4 + 3].color.a = static_cast<sf::Uint8>(ratio * 255);
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

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        //float angle = (std::rand() % 360) * PI / 180.f;
        
        //float angle = 225 * PI / 180;

        // get particle position. find out what square it's in. apply angle.
        sf::Vector2f particlePos = m_vertices[index * 4 + 0].position;
        const int gridX = particlePos.x / m_flow.tileSize.x;
        const int gridY = particlePos.y / m_flow.tileSize.y;
        float angle = m_flow.angleVector[gridX + gridY * (m_flow.width / m_flow.tileSize.x)];

        float speed = 200.f;
        sf::Time life{ sf::milliseconds((std::rand() % 2000) + 1000) };
        sf::Vector2f groupVel(sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed));
        m_particles[index].velocity = groupVel;
        m_particles[index].lifetime = life;

        // reset the position of the corresponding vertex
        m_vertices[index * 4 + 0].position = m_emitter;
        m_vertices[index * 4 + 1].position = m_emitter + sf::Vector2f(0, 2);
        m_vertices[index * 4 + 2].position = m_emitter + sf::Vector2f(2, 2);
        m_vertices[index * 4 + 3].position = m_emitter + sf::Vector2f(2, 0);
    }

    sf::Color topLeft;
    sf::Color topRight;
    sf::Color bottomLeft;
    sf::Color bottomRight;
    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    Flow m_flow;
};
