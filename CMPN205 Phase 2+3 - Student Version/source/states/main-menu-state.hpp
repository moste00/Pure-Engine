#pragma once 

#include <application.hpp>

class MainMenuState: public our::State {
    void onImmediateGui(){
        ImGui::Begin("Icy Tower 3D !");
        if(ImGui::Button("Play !",ImVec2(400,200))){
            getApp()->changeState("main") ;
        }
        else if(ImGui::Button("Exit", ImVec2(400, 200))){
            glfwDestroyWindow(getApp()->getWindow()); 
            glfwTerminate(); 
        }
        ImGui::End();
        glClear(GL_COLOR_BUFFER_BIT);
    }  
};
