#pragma once 

#include <application.hpp>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

class MainMenuState: public our::State {
    void onInitialize() {
        mciSendString("stop main", NULL, 0, NULL);
        mciSendString("close main", NULL, 0, NULL);

        mciSendString("open music/main-menu.mp3 type mpegvideo alias mainmenu", NULL, 0, NULL);
        mciSendString("play mainmenu repeat", NULL, 0, NULL);

        //This is a hack to cover a use-after-free memory corruption
        //Fix and change
        getApp()->registerState<Playstate>("main");
    }
    void onImmediateGui(){
        ImGui::Begin("Icy Tower 3D");
        if(ImGui::Button("Play !",ImVec2(400,200))){
            mciSendString("open music/main-loop.mp3 type mpegvideo alias main", NULL, 0, NULL);
            mciSendString("play main repeat", NULL, 0, NULL);

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
        mciSendString("stop mainmenu", NULL, 0, NULL);
        mciSendString("close mainmenu", NULL, 0, NULL);
    }
};
