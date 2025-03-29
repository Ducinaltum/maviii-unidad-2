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

	{
		//Agregar objeto PISO
		boxBody = NULL;

		b2BodyDef boxDef;
		boxDef.type = b2BodyType::b2_dynamicBody;
		boxDef.position = b2Vec2(400, 300);
		boxDef.allowSleep = false;

		//Esto tiene que ir antes o despu�s del fixture
		boxBody = phyWorld->CreateBody(&boxDef);

		//creamos la definici�n para nuestro fixture
		//Cambiar a box
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.friction = 1.0f;
		boxFixtureDef.density = 1.0f;

		b2PolygonShape boxShape;
		boxShape.SetAsBox(50.0f, 40.0f); // Box size (half-width, half-height)

		//establecemos la forma al fixture
		boxFixtureDef.shape = &boxShape;

		//le decimos al cuerpo rigido que instance el fixture y se lo establezca
		b2Fixture* pFloorFixture = boxBody->CreateFixture(&boxFixtureDef);
	}
	{
		//Agregar objeto PISO
		groundBody = NULL;

		b2BodyDef groundDef;
		groundDef.type = b2BodyType::b2_staticBody;
		groundDef.position = b2Vec2(400, 500);
		groundDef.angle = b2_pi / 6;

		//Esto tiene que ir antes o despu�s del fixture
		groundBody = phyWorld->CreateBody(&groundDef);

		//creamos la definici�n para nuestro fixture
		//Cambiar a box
		b2FixtureDef groundFixtureDef;
		groundFixtureDef.friction = 1.0f;
		groundFixtureDef.density = 1.0f;

		b2PolygonShape boxShape;
		boxShape.SetAsBox(400.0f, 100.0f); // Box size (half-width, half-height)

		//establecemos la forma al fixture
		groundFixtureDef.shape = &boxShape;

		//le decimos al cuerpo rigido que instance el fixture y se lo establezca
		b2Fixture* pFloorFixture = groundBody->CreateFixture(&groundFixtureDef);
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
			float friction = boxBody->GetFixtureList()->GetFriction() + 0.01f;
			friction = fmax(friction, 0);
			boxBody->GetFixtureList()->SetFriction(friction);
			groundBody->GetFixtureList()->SetFriction(friction);
			std::cout << friction << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			float friction = boxBody->GetFixtureList()->GetFriction() - 0.01f;
			friction = fmax(friction, 0);
			boxBody->GetFixtureList()->SetFriction(friction);
			groundBody->GetFixtureList()->SetFriction(friction);
			std::cout << friction << std::endl;
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