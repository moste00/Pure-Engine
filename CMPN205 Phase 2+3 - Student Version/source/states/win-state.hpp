#pragma once 

 #include <application.hpp>
 #include "play-state.hpp"
 #include "Windows.h"
 #pragma comment(lib, "Winmm.lib")

class WinState: public our::State {
    void onInitialize() {
        mciSendString("stop main", NULL, 0, NULL);
        mciSendString("close main", NULL, 0, NULL);

        mciSendString("open music/win.mp3 type mpegvideo alias win", NULL, 0, NULL);
        mciSendString("play win repeat", NULL, 0, NULL);

        //This is a hack to cover a use-after-free memory corruption
        //Fix and change
        getApp()->registerState<Playstate>("main");
    }

    void onImmediateGui(){
        ImGui::Begin("You Won !");
        if(ImGui::Button("Play Again",ImVec2(400,200))){
            mciSendString("open music/main-loop.mp3 type mpegvideo alias main", NULL, 0, NULL);
            mciSendString("play main repeat", NULL, 0, NULL);

            getApp()->changeState("main") ;
        }
        if(ImGui::Button("Exit To Main Menu", ImVec2(400, 200))){
            getApp()->changeState("main-menu");;
        }
        
        ImGui::SetWindowFontScale(3);
        ImGui::End();
        glClear(GL_COLOR_BUFFER_BIT);
    }  

    void onDestroy(){
        mciSendString("stop win", NULL, 0, NULL);
        mciSendString("close win", NULL, 0, NULL);
    }
};