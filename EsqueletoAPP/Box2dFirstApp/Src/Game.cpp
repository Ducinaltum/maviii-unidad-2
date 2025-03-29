#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
	// Inicializaci�n de la ventana y configuraci�n de propiedades
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom(); // Configuraci�n de la vista del juego
	InitPhysics(); // Inicializaci�n del motor de f�sica
}

// Configuraci�n de la vista del juego
void Game::SetZoom()
{
	View camara;
	// Posicionamiento y tama�o de la vista
	camara.setSize(800.0f, 600.0f);
	camara.setCenter(400.0f, 300.0f);
	wnd->setView(camara); // Asignar la vista a la ventana
}

// Inicializaci�n del motor de f�sica y los cuerpos del mundo f�sico
void Game::InitPhysics()
{
	// Inicializar el mundo f�sico con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Crear un renderer de debug para visualizar el mundo f�sico
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	direction = new b2Vec2(100, 100);
	{
		//Agregar objeto PISO
		cannonBall = NULL;

		b2BodyDef cannonBallDef;
		cannonBallDef.type = b2BodyType::b2_dynamicBody;
		cannonBallDef.position = b2Vec2(400, 300);
		cannonBallDef.bullet = true;
		cannonBallDef.linearDamping = 0;

		//Esto tiene que ir antes o despu�s del fixture
		cannonBall = phyWorld->CreateBody(&cannonBallDef);

		//creamos la definici�n para nuestro fixture
		//Cambiar a box
		b2FixtureDef cannonBallFixtureDef;
		cannonBallFixtureDef.friction = 0.0f;
		cannonBallFixtureDef.density = 1.0f;

		b2CircleShape circleShape;
		circleShape.m_radius = 25.0f;

		//establecemos la forma al fixture
		cannonBallFixtureDef.shape = &circleShape;

		//le decimos al cuerpo rigido que instance el fixture y se lo establezca
		b2Fixture* pFloorFixture = cannonBall->CreateFixture(&cannonBallFixtureDef);
	}
}

// Bucle principal del juego
void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor); // Limpiar la ventana
		DoEvents(); // Procesar eventos de entrada
		CheckCollitions(); // Comprobar colisiones
		UpdatePhysics(); // Actualizar la simulaci�n f�sica
		DrawGame(); // Dibujar el juego
		wnd->display(); // Mostrar la ventana
	}
}

// Procesamiento de eventos de entrada
void Game::DoEvents()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close(); // Cerrar la ventana si se presiona el bot�n de cerrar
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			direction->y += 10.0f;
			std::cout << direction->y << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			direction->y -= 10.0f;
			std::cout << direction->y << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			float force = 200000;
			b2Vec2 normalizedDirection(direction->x, direction->y);
			normalizedDirection.Normalize();
			b2Vec2 result(normalizedDirection.x * force, normalizedDirection.y * -force);
			cannonBall->SetTransform(b2Vec2(50,550), 0);
			cannonBall->SetLinearVelocity(b2Vec2(0,0));
			cannonBall->ApplyLinearImpulseToCenter(result, true);
			std::cout << "Shoot " << result.x<< " " << result.y << std::endl;
		}

	}
}

// Comprobaci�n de colisiones (a implementar m�s adelante)
void Game::CheckCollitions()
{
	// Implementaci�n de la comprobaci�n de colisiones
}

// Actualizaci�n de la simulaci�n f�sica
void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8); // Simular el mundo f�sico
	phyWorld->ClearForces(); // Limpiar las fuerzas aplicadas a los cuerpos
	phyWorld->DebugDraw(); // Dibujar el mundo f�sico para depuraci�n
}

// Dibujo de los elementos del juego
void Game::DrawGame()
{

}


// Destructor de la clase
Game::~Game(void)
{
}