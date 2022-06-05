#pragma once 

#include <application.hpp>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

class MainMenuState: public our::State {
    void onInitialize() {
        mciSendString("open \"music/main-menu.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
        mciSendString("play mp3 repeat", NULL, 0, NULL);
    }
    void onImmediateGui(){
        ImGui::Begin("Icy Tower 3D");
        if(ImGui::Button("Play !",ImVec2(400,200))){
            getApp()->changeState("main") ;
        }
        if(ImGui::Button("Exit", ImVec2(400, 200))){
            getApp()->exit();
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
