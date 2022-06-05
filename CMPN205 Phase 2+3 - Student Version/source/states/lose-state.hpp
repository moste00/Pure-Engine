#pragma once 

 #include <application.hpp>
#include "play-state.hpp"
#include "Windows.h"
#pragma comment(lib, "Winmm.lib")
class LoseState: public our::State {
    void onInitialize() {
        mciSendString("open \"music/lose.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
        mciSendString("play mp3 repeat", NULL, 0, NULL);

        //This is a hack to cover a use-after-free memory corruption
        //Fix and change
        getApp()->registerState<Playstate>("main");
    }

    void onImmediateGui(){
        
        ImGui::Begin("You Lost !");
        if(ImGui::Button("Play Again",ImVec2(400,200))){
            getApp()->changeState("main") ;
        }
        if(ImGui::Button("Exit To Main Menu", ImVec2(400, 200))){
            getApp()->changeState("main-menu");
        }
        
        ImGui::SetWindowFontScale(3);
        ImGui::End();
        glClear(GL_COLOR_BUFFER_BIT);
    }  

    void onDestroy(){
        mciSendString("stop mp3", NULL, 0, NULL);
        mciSendString("close mp3", NULL, 0, NULL);
    }
};