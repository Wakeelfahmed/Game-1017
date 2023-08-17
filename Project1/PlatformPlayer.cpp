#include "PlatformPlayer.h"
#include "Engine.h"
#include "DebugManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <cmath>
#include <iostream>
using namespace std;

PlatformPlayer::PlatformPlayer(SDL_Rect src, SDL_FRect dst) :AnimatedSprite(src, dst, STATE_IDLING),
m_grounded(false), m_facingLeft(false), m_maxVelX(9.0),
m_maxVelY(kJumpForce), m_grav(kGrav), m_drag(0.8)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	SetAnimation(m_state, 10, 0, 8, m_src.h * 2); // Initialize IDLE animation.
	m_enabled = true;
}

void PlatformPlayer::Update()
{
	static int i = 0;
	// Checking states.
	switch (m_state)
	{
	case STATE_IDLING:
		// Transition to run.
		if (EVMA::KeyPressed(SDL_SCANCODE_A) || EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			SetAnimation(STATE_RUNNING, 8, 0, 8, m_src.h * 6);//6
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -kJumpForce; // SetAccelY(-JUMPFORCE);
			m_grounded = false; // SetGrounded(false);
			SOMA::PlaySound("jump");
			SetAnimation(STATE_JUMPING, 15, 0, 5, m_src.h * 18);//18
			cout << i << endl;
		}

		else if (EVMA::KeyPressed(SDL_SCANCODE_C))
		{
			m_crouching = true; // Start crouching
			SetAnimation(STATE_CROUCHING, 8, 0, 3, m_src.h * 15); // Set crouching animation
		}

		break;

	case STATE_CROUCHING:
		// Move left and right while crouching.
		if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
		{
			m_accelX = -1.0; //Speed
			if (!m_facingLeft)
				m_facingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < kWidth - m_dst.w)
		{
			m_accelX = 1.0; //Speed
			if (m_facingLeft)
				m_facingLeft = false;
		}

		// Transition to standing if "c" key is pressed again.
		if (EVMA::KeyPressed(SDL_SCANCODE_C))
		{
			m_crouching = false; // Stop crouching
			SetAnimation(STATE_IDLING, 10, 0, 8, m_src.h * 2); // Set standing animation
		}
		break;

	case STATE_RUNNING:
		// Move left and right.
		if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
		{
			m_accelX = -1.5;
			if (!m_facingLeft)
				m_facingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < kWidth - m_dst.w)
		{
			m_accelX = 1.5;
			if (m_facingLeft)
				m_facingLeft = false;
		}
		// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -kJumpForce;
			m_grounded = false;
			SOMA::PlaySound("jump");
			SetAnimation(STATE_JUMPING, 10, 0, 3, m_src.h * 18);
		}
		// Transition to idle.
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			SetAnimation(STATE_IDLING, 10, 0, 8, m_src.h * 2);
		}
		break;
	case STATE_JUMPING:
		// Move in mid-air is cool.
		if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
		{
			m_accelX = -1.5;
			if (!m_facingLeft)
				m_facingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < kWidth - m_dst.w)
		{
			m_accelX = 1.5;
			if (m_facingLeft)
				m_facingLeft = false;
		}
		// Hit the ground, transition to run.
		if (m_grounded)
		{
			SetAnimation(STATE_RUNNING, 10, 0, 8, m_src.h * 2);
		}
		break;
	}
	if (!m_enabled) {
		SetAnimation(STATE_DEATH, 10, 0, 8, m_src.h * 27); //full death
		m_enabled = 1;
		Animate();
		m_state = STATE_IDLING;
		//SetAnimation(STATE_IDLING, 10, 0, 8, m_src.h * 2); // Initialize IDLE animation.
	}
	m_enabled = 1;


	// Player movement. X axis first.
	m_velX += m_accelX; // Add acceleration to velocity.
	m_velX *= (m_grounded ? m_drag : 1.0); // Cheeky deceleration.
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX);
	m_dst.x += (float)m_velX; // May have to cast to (int)

	if (m_dst.y > 615) {
		m_dst.y = 615;
		m_velY = 0.0;
		SetGrounded(true); // Assuming player is grounded when on the platform
	}
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), m_maxVelY); // (m_grav * 5.0)
	m_dst.y += (float)m_velY;
	m_accelX = m_accelY = 0.0; // Resetting accel every frame.
	// Invoke the animation.
	Animate();

	//i++;
}

void PlatformPlayer::Render()
{
	DEMA::DrawRect(*GetDst(), true, { 0, 0, 0, 64 });
	SDL_RenderCopyExF(REMA::GetRenderer(), TEMA::GetTexture("player"),
		&m_src, &m_dst, 0.0, NULL, (m_facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void PlatformPlayer::Stop()
{
	StopX();
	StopY();
}

void PlatformPlayer::StopX() { m_velX = 0.0; }

void PlatformPlayer::StopY() { m_velY = 0.0; }

void PlatformPlayer::SetAccelX(double accel) { m_accelX = accel; }

void PlatformPlayer::SetAccelY(double accel) { m_accelY = accel; }

bool PlatformPlayer::IsGrounded() { return m_grounded; }

void PlatformPlayer::SetGrounded(bool grounded) { m_grounded = grounded; }

double PlatformPlayer::GetVelX() { return m_velX; }

double PlatformPlayer::GetVelY() { return m_velY; }

void PlatformPlayer::SetX(float x) { m_dst.x = x; }

void PlatformPlayer::SetY(float y) { m_dst.y = y; }