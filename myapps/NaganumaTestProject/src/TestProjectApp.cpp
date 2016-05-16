#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"
#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"

#include <cereal/archives/binary.hpp>
#include "CinderCereal.h"
#define RUNTIME_APP_CEREALIZATION

#include "Watchdog.h"
#include "CinderImGui.h"
#include "runtime_app.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TestProjectApp : public App {
public:
	void setup() override;
	void update() override;
	void draw() override;
	
	void mouseDown( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
	void mouseWheel( MouseEvent event ) override;
	void mouseMove( MouseEvent event ) override;
	void mouseDrag( MouseEvent event ) override;
	void keyDown( KeyEvent event ) override;
	void keyUp( KeyEvent event ) override;
	void resize() override;
	void fileDrop( FileDropEvent event ) override;
	
	void cleanup() override;
	
	virtual void save( cereal::BinaryOutputArchive &ar );
	virtual void load( cereal::BinaryInputArchive &ar );
	
	float				mBackground;
	vec4				mBackgroundColor;
	
	gl::GlslProgRef		mGlslProg;
	gl::BatchRef		mBatch, mPlane,mmBatch;
	gl::Texture2dRef	mTexture;
	
	CameraPersp			mCamera;
	CameraUi			mCameraUi;

    float mBackground;
    float mBackgroundcolor[4];

};

void TestProjectApp::setup()
{
	// getWindow()->setAlwaysOnTop();
	
	// Initialize the Camera and its UI
	mCamera = CameraPersp( getWindowWidth(), getWindowHeight(), 50.0f, 0.1f, 100.0f );
	mCamera.lookAt( vec3(5,2,0), vec3(0) );
	mCameraUi = CameraUi( &mCamera );
<<<<<<< HEAD:myapps/NaganumaTestProject/src/TestProjectApp.cpp


    vector<vec3> positions;
    vector<ColorA>colors;

	// create batch advanced
	mBatch = gl::Batch::create( geom::Cone(), gl::getStockShader( gl::ShaderDef().lambert() ) );

    auto bufferLayout = geom::BufferLayout();
    bufferLayout.append(geom::POSITION, 3, 0, 0);
    vector<vec3> points = {vec3(0.0f)};
    auto vbo = gl::Vbo::create(GL_ARRAY_BUFFER,points);
    auto sourece = geom::Sphere().subdivisions(64);
    auto vboMesh = gl::VboMesh::create(points.size(),GL_POINTS,{
        {bufferLayout,vbo}
    });
    auto glslProg = gl::getStockShader(gl::ShaderDef().lambert());
    mmBatch = gl::Batch::create(vboMesh,glslProg);


    //Plane Batch
=======
	
	// create plane batch
>>>>>>> upstream/master:apps/TestProject/src/TestProjectApp.cpp
	mPlane = gl::Batch::create( geom::Plane().subdivisions( ivec2( 64 ) ).size( vec2( 100.0f ) ) >> geom::Lines(), gl::getStockShader( gl::ShaderDef().lambert() ) );
	
	// load texture
	mTexture = gl::Texture2d::create( loadImage( loadAsset( "iceland.jpg" ) ) );


    mBackground = 0.5f;

	// initialize ui
	ui::initialize();
<<<<<<< HEAD:myapps/NaganumaTestProject/src/TestProjectApp.cpp



    try {
        mGlslProg = gl::GlslProg::create( app::loadAsset( "shader.vert" ), app::loadAsset( "shader.frag" ) );
        mGlslProg->uniform( "uTexture", 0 );
    }
    catch( const std::exception &e ) {
        CI_LOG_EXCEPTION( "exception caught loading fxaa.vert / frag", e );
    }


=======
	
	// create advanced batch
	// Create my data
	vector<vec3> positions;
	vector<ColorA> colors;
	for( size_t i = 0; i < 10000; ++i ) {
		positions.push_back( randVec3() * randFloat( 0, 100 ) );
		colors.push_back( ColorA( randFloat( 0.9f, 1.0f ), randFloat( 0.6f, 0.8f ), randFloat( 0.9f, 1.0f ), 0.2f ) );
	}
	
	// Describe the data in terms of what it is, what dimensions it has, etc
	auto positionsLayout = geom::BufferLayout();
	positionsLayout.append( geom::POSITION, 3, 0, 0 );
	auto colorsLayout = geom::BufferLayout();
	colorsLayout.append( geom::COLOR, 4, 0, 0 );
	
	// Upload my data to the GPU through a VBO
	auto positionsVbo = gl::Vbo::create( GL_ARRAY_BUFFER, positions );
	auto colorsVbo = gl::Vbo::create( GL_ARRAY_BUFFER, colors );
	
	// Link everything together in a VboMesh
	auto vboMesh	= gl::VboMesh::create( positions.size(), GL_POINTS,
	{
		{ positionsLayout, positionsVbo },
		{ colorsLayout, colorsVbo }
	} );
	
	// watch the shader
	wd::watch( "shader.*", [this, vboMesh]( const fs::path &path ) {
		try {
			// create a shader
			auto glslProg	= gl::GlslProg::create( gl::GlslProg::Format()
											   .vertex( loadAsset( "shader.vert" ) )
											   .fragment( loadAsset( "shader.frag" ) ) );
			// linking my shader to my vbo mesh
			if( glslProg ) {
				mBatch = gl::Batch::create( vboMesh, glslProg );
			}
		}
		catch( gl::GlslProgExc exc ) {
			console() << exc.what() << endl;
		}
	} );
	
	mBackgroundColor = vec4(0.5f);
>>>>>>> upstream/master:apps/TestProject/src/TestProjectApp.cpp
}

void TestProjectApp::update()
{
<<<<<<< HEAD:myapps/NaganumaTestProject/src/TestProjectApp.cpp
	{//これでくくると違ったものが別々に現れる
		ui::ScopedWindow window( "Params" );
	}

    ui::DragFloat("Background", &mBackground,0.01f,0.0f,1.0f);
    ui::Text("SomeText");
    ui::ColorEdit4("BackgroundColor", &mBackgroundcolor[0]);
    ui::Image(mTexture, mTexture->getSize()/4);
=======

	
>>>>>>> upstream/master:apps/TestProject/src/TestProjectApp.cpp
}

void TestProjectApp::draw()
{
	
<<<<<<< HEAD:myapps/NaganumaTestProject/src/TestProjectApp.cpp
	gl::clear( Color::gray( mBackground ) );
=======
	gl::clear( Color::black() );
>>>>>>> upstream/master:apps/TestProject/src/TestProjectApp.cpp
	
	gl::ScopedMatrices scopedMatrices;
	gl::ScopedDepth	scopedDepth( true );
	gl::setMatrices( mCamera );
	
	gl::ScopedBlendAdditive scopedBlend;
	gl::ScopedTextureBind scopedTex0( mTexture );
	gl::ScopedColor scopedColor( ColorA::gray( 1.0f, 0.2f ) );
	
	if( mBatch ) {
		mBatch->draw();
	}
	mPlane->draw();
    mmBatch->draw();


    //---------
    if( ! mGlslProg )
        return;

    const int w = getWindowWidth();
    const int h = getWindowHeight();

    gl::ScopedGlslProg glslScope( mGlslProg );
    mGlslProg->uniform( "uExtends", vec4( 1.0f / w, 1.0f / h, (float) w, (float) h ) );
}



void TestProjectApp::mouseDown( MouseEvent event ) 
{
	mCameraUi.mouseDown( event );
}
void TestProjectApp::mouseUp( MouseEvent event ) 
{
	mCameraUi.mouseUp( event );
}
void TestProjectApp::mouseWheel( MouseEvent event ) 
{
	mCameraUi.mouseWheel( event );
}
void TestProjectApp::mouseMove( MouseEvent event ) 
{
}
void TestProjectApp::mouseDrag( MouseEvent event ) 
{
	mCameraUi.mouseDrag( event );
}

void TestProjectApp::keyDown( KeyEvent event ) 
{
}
void TestProjectApp::keyUp( KeyEvent event ) 
{
}
void TestProjectApp::resize() 
{
}
void TestProjectApp::fileDrop( FileDropEvent event ) 
{
}

void TestProjectApp::cleanup() 
{
}

void TestProjectApp::save( cereal::BinaryOutputArchive &ar )
{
}
void TestProjectApp::load( cereal::BinaryInputArchive &ar )
{
}

<<<<<<< HEAD:myapps/NaganumaTestProject/src/TestProjectApp.cpp


CINDER_RUNTIME_APP( TestProjectApp, RendererGl, App::SettingsFn()
#ifndef DISABLE_RUNTIME_COMPILED_APP
=======
CINDER_RUNTIME_APP( TestProjectApp, RendererGl( RendererGl::Options().msaa( 8 ) ), []( App::Settings *settings ) {
	//settings->setAlwaysOnTop();
}
#ifndef DISABLE_RUNTIME_COMPILATION
>>>>>>> upstream/master:apps/TestProject/src/TestProjectApp.cpp
// The interpreter needs to know about the blocks we are using
,[] ( cling::Interpreter *interpreter ) {
   // We need to find the path starting from the location of the app
   auto appRoot = getAppPath().parent_path().parent_path().parent_path();
   auto cinderRoot = appRoot.parent_path().parent_path() / "cinder";
   auto blocksFolder = cinderRoot / "blocks";
   
   // Header-only blocks are easily added by just providing the include path
   interpreter->AddIncludePath( ( blocksFolder / "SimplexNoise/include" ).string() );
   interpreter->AddIncludePath( ( blocksFolder / "SpacePartitioning/include" ).string() );
   interpreter->AddIncludePath( ( blocksFolder / "Watchdog/include" ).string() );
   
   // Some blocks requires the main include folder but also the include folder of the library it wraps
   interpreter->AddIncludePath( ( blocksFolder / "Cinder-Cereal/include" ).string() );
   interpreter->AddIncludePath( ( blocksFolder / "Cinder-Cereal/lib/cereal/include" ).string() );
   
   // Some other blocks with .cpp files might be a bit more tricky especially when
   // there's some #defines that need to be processed before the rest like in Cinder-ImGui
   auto imguiFolder = blocksFolder / "Cinder-ImGui";
   interpreter->AddIncludePath( ( imguiFolder / "lib/imgui" ).string() );
   interpreter->AddIncludePath( ( imguiFolder / "include" ).string() );
   interpreter->loadFile( ( imguiFolder / "include/CinderImGui.h" ).string(), false );
   interpreter->enableRawInput();
   interpreter->declare( ci::loadString( ci::loadFile( imguiFolder / "lib/imgui/imgui_draw.cpp" ) ) + "\n" + ci::loadString( ci::loadFile( imguiFolder / "lib/imgui/imgui.cpp" ) ) + "\n" + ci::loadString( ci::loadFile( imguiFolder / "src/CinderImGui.cpp" ) ) );
   interpreter->enableRawInput( false );
}
#endif
)
