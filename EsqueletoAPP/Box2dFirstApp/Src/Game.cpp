#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
    // Inicialización de la ventana y configuración de propiedades
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom(); // Configuración de la vista del juego
    InitPhysics(); // Inicialización del motor de física
}

// Configuración de la vista del juego
void Game::SetZoom()
{
    View camara;
    // Posicionamiento y tamaño de la vista
    camara.setSize(800.0f, 600.0f);
    camara.setCenter(400.0f, 300.0f);
    wnd->setView(camara); // Asignar la vista a la ventana
}

// Inicialización del motor de física y los cuerpos del mundo físico
void Game::InitPhysics()
{
    // Inicializar el mundo físico con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Crear un renderer de debug para visualizar el mundo físico
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    {
        //Agregar objeto BLOQUE
        blockBody = NULL;

        b2BodyDef blockBodyDef;
        blockBodyDef.type = b2BodyType::b2_dynamicBody;
        blockBodyDef.position = b2Vec2(400, 0);
        blockBodyDef.angle = 3.14 / 4;

        //Esto tiene que ir antes o después del fixture
        blockBody = phyWorld->CreateBody(&blockBodyDef);

        //creamos la definición para nuestro fixture
        //Cambiar a box
        b2FixtureDef blockFixtureDef;
        blockFixtureDef.friction = 0.3f;
        blockFixtureDef.density = 10.0f;
        blockFixtureDef.restitution = 0.5f;

        b2PolygonShape blockShape;
        blockShape.SetAsBox(50.0f, 10.0f); // Box size (half-width, half-height)
        //establecemos la forma al fixture
        blockFixtureDef.shape = &blockShape;

        //le decimos al cuerpo rigido que instance el fixture y se lo establesca
        b2Fixture* pBlockFixture = blockBody->CreateFixture(&blockFixtureDef);
    }
    {
        //Agregar objeto PISO
        floorBody = NULL;

        b2BodyDef blockFloorDef;
        blockFloorDef.type = b2BodyType::b2_staticBody;
        //set
        blockFloorDef.position = b2Vec2(400, 590);

        //Esto tiene que ir antes o después del fixture
        floorBody = phyWorld->CreateBody(&blockFloorDef);

        //creamos la definición para nuestro fixture
        //Cambiar a box
        b2FixtureDef floorFixtureDef;
        floorFixtureDef.friction = 0.3f;
        floorFixtureDef.density = 1.0f;

        b2PolygonShape boxShape;
        boxShape.SetAsBox(400.0f, 10.0f); // Box size (half-width, half-height)

        //establecemos la forma al fixture
        floorFixtureDef.shape = &boxShape;

        //le decimos al cuerpo rigido que instance el fixture y se lo establezca
        b2Fixture* pFloorFixture = floorBody->CreateFixture(&floorFixtureDef);
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
        UpdatePhysics(); // Actualizar la simulación física
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
            wnd->close(); // Cerrar la ventana si se presiona el botón de cerrar
            break;
        }
    }
}

// Comprobación de colisiones (a implementar más adelante)
void Game::CheckCollitions() {}

// Actualización de la simulación física
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); // Simular el mundo físico
    phyWorld->ClearForces(); // Limpiar las fuerzas aplicadas a los cuerpos
    phyWorld->DebugDraw(); // Dibujar el mundo físico para depuración
}

// Dibujo de los elementos del juego
void Game::DrawGame() {}

// Destructor de la clase
Game::~Game(void){ }