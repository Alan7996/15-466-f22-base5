#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	void gameWin();
	void gameLose();

	//----- game state -----
	enum GameState{
		PLAYING,
		VICTORY,
		DEFEAT
	} gameState;

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;

	std::vector<Scene::Drawable *> cones;
	glm::vec3 reset_spawn = glm::vec3(-20.0f, -20.0f, 0.0f);
	uint8_t active_bullet_count = 0;
	uint8_t inactive_bullet_count = 0;
	uint8_t total_bullet_count = 0;

	float elapsed_time_since = 0;
	float cone_interval = 3;
	bool check_time = true;
	float coneSpeed = 2.0f;

	std::string displayText = "";
};
