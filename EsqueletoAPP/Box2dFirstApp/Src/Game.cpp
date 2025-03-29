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
    ballBody->ApplyLinearImpulse(b2Vec2(5000000, 0), b2Vec2(400, 300), true);
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
        //Agregar objeto BLOQUE
        ballBody = NULL;

        b2BodyDef ballBodyDef;
        ballBodyDef.type = b2BodyType::b2_dynamicBody;
        ballBodyDef.position = b2Vec2(400, 300);

        //Esto tiene que ir antes o despu�s del fixture
        ballBody = phyWorld->CreateBody(&ballBodyDef);

        //creamos la definici�n para nuestro fixture
        //Cambiar a box
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.friction = 0.3f;
        ballFixtureDef.density = 10.0f;
        ballFixtureDef.restitution = 1.0f;

        b2CircleShape ballShape;
        ballShape.m_radius = 25;
        //establecemos la forma al fixture
        ballFixtureDef.shape = &ballShape;

        //le decimos al cuerpo rigido que instance el fixture y se lo establesca
        b2Fixture* pBlockFixture = ballBody->CreateFixture(&ballFixtureDef);
    }
    for(int i = 0; i < 4; i++)
    {
        //Agregar objeto PISO
        wallsBodies[i] = NULL;

        b2BodyDef blockFloorDef;
        blockFloorDef.type = b2BodyType::b2_staticBody;
        blockFloorDef.position = b2Vec2(0, 0);
        switch (i)
        {
        case 0:
            blockFloorDef.position = b2Vec2(5, 300);
            break;
        case 1:
            blockFloorDef.position = b2Vec2(400, 5);
            break;
        case 2:
            blockFloorDef.position = b2Vec2(795, 300);
            break;
        case 3:
            blockFloorDef.position = b2Vec2(400, 595);
            break;
        }


        //Esto tiene que ir antes o despu�s del fixture
        wallsBodies[i] = phyWorld->CreateBody(&blockFloorDef);

        //creamos la definici�n para nuestro fixture
        //Cambiar a box
        b2FixtureDef floorFixtureDef;
        floorFixtureDef.friction = 0.3f;
        floorFixtureDef.density = 0.10f;

        b2PolygonShape boxShape;
        switch (i)
        {
        case 0:
        case 2:
            boxShape.SetAsBox(5.0f, 300.0f); // Box size (half-width, half-height)
            break;
        case 1:
        case 3:
            boxShape.SetAsBox(400.0f, 5.0f); // Box size (half-width, half-height)
            break;
        }

        //establecemos la forma al fixture
        floorFixtureDef.shape = &boxShape;

        //le decimos al cuerpo rigido que instance el fixture y se lo establezca
        b2Fixture* pFloorFixture = wallsBodies[i]->CreateFixture(&floorFixtureDef);
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
{ }