#include "game.h"

void LGame::loadGame()
{
    init();

    //Setup chess pieces and load media
    loadMedia(gCell[BLACK_PAWN], "pictures/PNGs/No shadow/1x/b_pawn.png");
    gCell[BLACK_PAWN].chessPiece = true, gCell[BLACK_PAWN].isFlip = true;

    loadMedia(gCell[WHITE_PAWN], "pictures/PNGs/No shadow/1x/w_pawn.png");
    gCell[WHITE_PAWN].chessPiece = true;

    loadMedia(gCell[BLACK_BISHOP], "pictures/PNGs/No shadow/1x/b_bishop.png");
    gCell[BLACK_BISHOP].chessPiece = true, gCell[BLACK_BISHOP].isFlip = true;

    loadMedia(gCell[WHITE_BISHOP], "pictures/PNGs/No shadow/1x/w_bishop.png");
    gCell[WHITE_BISHOP].chessPiece = true;

    loadMedia(gCell[BLACK_KNIGHT], "pictures/PNGs/No shadow/1x/b_knight.png");
    gCell[BLACK_KNIGHT].chessPiece = true, gCell[BLACK_KNIGHT].isFlip = true;

    loadMedia(gCell[WHITE_KNIGHT], "pictures/PNGs/No shadow/1x/w_knight.png");
    gCell[WHITE_KNIGHT].chessPiece = true;

    loadMedia(gCell[BLACK_ROOK], "pictures/PNGs/No shadow/1x/b_rook.png");
    gCell[BLACK_ROOK].chessPiece = true, gCell[BLACK_ROOK].isFlip = true;

    loadMedia(gCell[WHITE_ROOK], "pictures/PNGs/No shadow/1x/w_rook.png");
    gCell[WHITE_ROOK].chessPiece = true;

    loadMedia(gCell[BLACK_QUEEN], "pictures/PNGs/No shadow/1x/b_queen.png");
    gCell[BLACK_QUEEN].chessPiece = true, gCell[BLACK_QUEEN].isFlip = true;

    loadMedia(gCell[WHITE_QUEEN], "pictures/PNGs/No shadow/1x/w_queen.png");
    gCell[WHITE_QUEEN].chessPiece = true;

    loadMedia(gCell[BLACK_KING], "pictures/PNGs/No shadow/1x/b_king.png");
    gCell[BLACK_KING].chessPiece = true, gCell[BLACK_KING].isFlip = true;

    loadMedia(gCell[WHITE_KING], "pictures/PNGs/No shadow/1x/w_king.png");
    gCell[WHITE_KING].chessPiece = true;

    loadMedia(blackCell, "pictures/PNGs/No shadow/1x/b_cell.png");
    blackCell.chessPiece = true;

    loadMedia(whiteCell, "pictures/PNGs/No shadow/1x/w_cell.png");
    whiteCell.chessPiece = true;

    setCellPosition();

    setCellType();
}

void LGame::playGame()
{
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Load chessboard
        for(int i=0; i<SIZE; ++i)
            for(int j=0; j<SIZE; ++j)
            {
                if((i + j)&1)
                    whiteCell.render(gRenderer, topLeftCellPosition[i][j].x, topLeftCellPosition[i][j].y);
                else
                    blackCell.render(gRenderer, topLeftCellPosition[i][j].x, topLeftCellPosition[i][j].y);
            }

        for(int i=0; i<SIZE; ++i)
            for(int j=0; j<SIZE; ++j)
            {
                if(cellType[i][j] != EMPTY)
                    gCell[cellType[i][j]].render(gRenderer, topLeftCellPosition[i][j].x, topLeftCellPosition[i][j].y);
            }

        //Update screen
        SDL_RenderPresent( gRenderer );
    }
}

bool LGame::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

//Push piece on chess board
void LGame::setCellType()
{
    for(int i=0; i<SIZE; ++i)
    {
        for(int j=0; j<SIZE; ++j)
        {
            cellType[i][j] = EMPTY;
        }
    }

    for(int i=0; i<SIZE; ++i)
    {
        cellType[1][i] = BLACK_PAWN;
        cellType[SIZE-2][i] = WHITE_PAWN;
    }

    cellType[0][0] = cellType[0][SIZE-1] = BLACK_ROOK;
    cellType[0][1] = cellType[0][SIZE-2] = BLACK_KNIGHT;
    cellType[0][2] = cellType[0][SIZE-3] = BLACK_BISHOP;
    cellType[0][3] = BLACK_QUEEN, cellType[0][SIZE-4] = BLACK_KING;
    
    cellType[SIZE-1][0] = cellType[SIZE-1][SIZE-1] = WHITE_ROOK;
    cellType[SIZE-1][1] = cellType[SIZE-1][SIZE-2] = WHITE_KNIGHT;
    cellType[SIZE-1][2] = cellType[SIZE-1][SIZE-3] = WHITE_BISHOP;
    cellType[SIZE-1][3] = WHITE_QUEEN, cellType[SIZE-1][SIZE-4] = WHITE_KING;
}

bool LGame::loadString(LTexture &curTexture, const std::string &path, const std::string &str)
{
    bool success = true;

    if(!curTexture.loadString(gRenderer, path, str))
    {
        printf("Failed to load string texture\n");
        success = false;
    }

    return success;
}

bool LGame::loadMedia(LTexture &curTexture, const std::string &path)
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if( !curTexture.loadFromFile(path, gRenderer) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	return success;
}

//Set cell top left coordinate
void LGame::setCellPosition()
{
    for(int i=0; i<SIZE; ++i)
    {
        for(int j=0; j<SIZE; ++j)
            topLeftCellPosition[j][i].x = i * LENGTH, topLeftCellPosition[j][i].y = j * LENGTH;
    }
}

LGame::LGame()
{
    gWindow = NULL;
    gRenderer = NULL;    
}

LGame::~LGame()
{
	//Free loaded images
	// gButtonSpriteSheetTexture.free();
	//Destroy window	
    
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}