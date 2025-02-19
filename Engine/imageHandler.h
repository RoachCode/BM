#pragma once
#include "filesys.h"
#include "view.h"
#include "tilemap.h"
#include "maps.h"
#include "light.h"

class ImageHandler : protected View
{
public:
	const char lightFrag[897] =
		"uniform vec2 resolution;"
		"uniform sampler2D sampler_normal;"
		"uniform sampler2D sampler_light;"
		"uniform vec3 light_pos;"
		"uniform vec3 light_color;"
		"uniform vec3 ambient_color = vec3(0.5, 0.5, 0.5);"
		"uniform float ambient_intensity;"
		"uniform vec3 falloff;"
		"void main()"
		"{"
		"vec2 coord = gl_TexCoord[0].xy;"
		"vec3 normal_map = texture2D(sampler_normal, coord).rgb;"
		"vec3 light_map = texture2D(sampler_light, coord).rgb;"
		"vec3 lightDir = vec3((light_pos.xy - gl_FragCoord.xy) / resolution.xy, light_pos.z); "
		"lightDir.x *= resolution.x / resolution.y;"
		"float D = length(lightDir);"
		"vec3 N = normalize(normal_map * 2.0 - 1.0);"
		//"vec3 N = -1.0 * normalize(normal_map * 2.0 - 1.0);"
		"vec3 L = normalize(lightDir.xyz);"
		"vec3 diffuse = light_color.rgb * max(dot(N, L), 0.0);"
		"vec3 ambient = ambient_color * ambient_intensity;"
		"float attenuation = 1.0 / (falloff.x + (falloff.y * D) + falloff.z * D * D);"
		"vec3 intensity = ambient + diffuse * attenuation;"
		"gl_FragColor = vec4(light_map + intensity, 1.0);"
		"}";

	const char normalsFrag[155] =
		"uniform sampler2D sampler_normal;"
		"void main(void)"
		"{"
		"vec3 normal_map = texture2D(sampler_normal, gl_TexCoord[0].xy).rgb;"
		"gl_FragColor = vec4(normal_map, 1.0);"
		"}";

    uint8_t zDepth;
    TileMap tileMapA;
    TileMap tileMapB;
    TileMap tileMapC;
    TileMap tileMapD;
    TileMap tileMapE;
    TileMap tileMapF;
    TileMap tileMapG;
    TileMap tileMapH;
    TileMap tileMapI;
    TileMap tileMapJ;

	TileMap tileMapNormalA;
	TileMap tileMapNormalB;
	TileMap tileMapNormalC;
	TileMap tileMapNormalD;
	TileMap tileMapNormalE;
	TileMap tileMapNormalF;
	TileMap tileMapNormalG;
	TileMap tileMapNormalH;
	TileMap tileMapNormalI;
	TileMap tileMapNormalJ;

    sf::Image tileImage;
    std::vector<TileMap*> tilemapVector;
    std::vector<TileMap*> tilemapNormalVector;

    sf::RenderTexture tilemapRenderBack;//
    sf::RenderTexture tilemapRenderFront;

	sf::Shader lights_shader;
	sf::Shader normals_shader;

	sf::Image tileNormalImage;
	sf::RenderTexture normalsRender;

	Light light;

	sf::RenderTexture lightRender;
	sf::RenderTexture pass_normals;
	sf::Texture normal_map;
	sf::Texture diffuse_map;
	//sf::Sprite spriteT;

    ImageHandler();

    void loadWestKagar();
	void loadLights();
    bool checkBounds(int direction, sf::Vector2i position);
};