#include<stdio.h>
#include<stdlib.h>
#include"SDL.h"
#include"SDL_events.h"


typedef struct wormHead
{
  SDL_Rect rHead ;
  struct wormSegment* pWormSegment ;
  //int8_t siNumberOfSegments ;  
} wormHead ;

typedef struct wormSegment
{
    SDL_Rect rSegment ;
    struct wormSegment* pWormSegment ;
} wormSegment ;

int main( int argc, char* argv[] )
{
    wormHead whHungryWorm ;

    SDL_Window* wWindow = NULL ;

    SDL_Surface* srfcScreen = NULL ;

    //SDL_Surface* srfcWormSegmentImage = NULL ;

    SDL_Surface* srfcWormHeadImage = NULL ;

    SDL_DisplayMode dmDisplayMode ;

    SDL_Rect rPlayArea ;

    SDL_Rect rGrass ;

    SDL_Event eKeyboardInput ;

    SDL_bool boGameLoop = SDL_TRUE ;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) != 0 )
    {
        fprintf( stderr, "Failed to initialise SDL: %s", SDL_GetError() ) ;

        return 1 ;
    }

    wWindow = SDL_CreateWindow( "SNACK", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP ) ;

    if( wWindow == NULL )
    {
        fprintf( stderr, "Failed to create window: %s", SDL_GetError() ) ;

        return 1 ;
    }

    SDL_GetWindowDisplayMode( wWindow, &dmDisplayMode ) ;

    rPlayArea.x = ( dmDisplayMode.w - dmDisplayMode.h  ) / 2 ;
    rPlayArea.y = dmDisplayMode.h / 50 ;
    rPlayArea.h  = dmDisplayMode.h - ( rPlayArea.y * 2 ) ;
    rPlayArea.w = dmDisplayMode.h ;

    rGrass.y = 0 ;
    rGrass.x = 0 ;
    rGrass.h = dmDisplayMode.h / 50 ;
    rGrass.w = dmDisplayMode.w ;

    whHungryWorm.rHead.x = dmDisplayMode.w / 2 ;
    whHungryWorm.rHead.y = dmDisplayMode.h / 2 ;
    whHungryWorm.rHead.h = rPlayArea.h / 15 ;
    whHungryWorm.rHead.w = rPlayArea.w / 15 ;

    srfcScreen = SDL_GetWindowSurface( wWindow ) ;

    srfcWormHeadImage = SDL_CreateRGBSurface( 0, whHungryWorm.rHead.w, whHungryWorm.rHead.h, 32, 0, 0, 0, 0 ) ;

    SDL_FillRect( srfcScreen, NULL, SDL_MapRGB( srfcScreen->format, 64, 64, 64 ) ) ;

    SDL_FillRect( srfcScreen, &rPlayArea, SDL_MapRGB( srfcScreen->format, 127, 72, 7 ) ) ;

    SDL_FillRect( srfcScreen, &rGrass, SDL_MapRGB( srfcScreen->format, 0, 255, 0 ) ) ;

    /* Manually setting a pixel!

    Uint32* pix = (Uint32*)srfcScreen->pixels ;

    for( int i = rPlayArea.x; i < rPlayArea.w ; i++ )
    {
        pix[i] = 0xFFFF0000 ;
    }

    */

    //SDL_memset(srfcScreen->pixels, SDL_MapRGBA( srfcScreen->format, 255, 0, 0, 0 ), ( dmDisplayMode.h / 50 )  * srfcScreen->pitch);

    //SDL_FillRect( srfcSurface, &rDisplayBounds, SDL_MapRGB( srfcSurface->format, 0, 0, 255 ) ) ;
    // Having the taskbar at top of screen, and using a maximised window, results in a loss of screen space when using
    // GetDisplayUsableBounds.

    while( boGameLoop )
    {
        SDL_FillRect( srfcScreen, &whHungryWorm.rHead, SDL_MapRGB( srfcScreen->format, 127, 72, 7 ) ) ;
        
        while( SDL_PollEvent( &eKeyboardInput ) != 0 )
        {
            if( eKeyboardInput.type == SDL_QUIT )
            {
                boGameLoop = SDL_FALSE ;
            }
            else if( eKeyboardInput.type == SDL_KEYDOWN )
            {
                switch( eKeyboardInput.key.keysym.sym )
                {
                    case SDLK_ESCAPE:

                        boGameLoop = SDL_FALSE ;

                        break ;

                    case SDLK_UP:

                        whHungryWorm.rHead.y =  whHungryWorm.rHead.y - ( rPlayArea.h / 150 ) ;

                        if(  whHungryWorm.rHead.y <= rPlayArea.y ) 
                        {
                             whHungryWorm.rHead.y = rPlayArea.y + 1 ;
                        }
                        break ;

                    case SDLK_DOWN:

                        whHungryWorm.rHead.y =  whHungryWorm.rHead.y + ( rPlayArea.h / 150 ) ;
            
                        if( (  whHungryWorm.rHead.y +  whHungryWorm.rHead.h ) >= rPlayArea.y + rPlayArea.h ) 
                        {
                            whHungryWorm.rHead.y = ( rPlayArea.y + rPlayArea.h ) -  whHungryWorm.rHead.h ;
                        }

                        break ;

                    case SDLK_RIGHT:

                        whHungryWorm.rHead.x = whHungryWorm.rHead.x + ( rPlayArea.w / 150 ) ;

                        if( ( whHungryWorm.rHead.x + whHungryWorm.rHead.w) >= ( rPlayArea.x + rPlayArea.w ) ) 
                        {
                            whHungryWorm.rHead.x = ( rPlayArea.x + rPlayArea.w ) - whHungryWorm.rHead.w ;
                        }

                        break ;

                    case SDLK_LEFT:

                        whHungryWorm.rHead.x = whHungryWorm.rHead.x - ( rPlayArea.w / 150 ) ;

                        if( whHungryWorm.rHead.x <= rPlayArea.x ) 
                        {
                            whHungryWorm.rHead.x = rPlayArea.x + 1 ;
                        }

                        break ;

                    default:

                        break ;
                }
            }
        }

        SDL_FillRect( srfcWormHeadImage, NULL, SDL_MapRGB( srfcWormHeadImage->format, 211, 114, 131 ) ) ;

        SDL_BlitSurface( srfcWormHeadImage, NULL, srfcScreen, &whHungryWorm.rHead ) ;

        SDL_UpdateWindowSurface( wWindow ) ;

        SDL_Delay( 1 ) ;
    }                

    SDL_FreeSurface( srfcScreen ) ;

    SDL_FreeSurface( srfcWormHeadImage ) ;

    SDL_DestroyWindow( wWindow ) ;

    SDL_Quit() ;

    return 0 ;
}