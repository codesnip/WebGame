/*
Copyright (C) 2011 WebGame project.
*/

#include "../include/WebGame.h"
#include "../include/IntConnectedList.h"
#include "../include/HTTP.h"
#include <iostream>
#include <limits>
int main()
{
//    cWebGame WebGame;
//    WebGame.StartMainLoop();



  // cIntConnectedList IntConnectedList(100);
  //  IntConnectedList.Add(0);
//IntConnectedList.Add(1);
   // IntConnectedList.Add(2);
   // IntConnectedList.Add(3);
   // IntConnectedList.Remove(3);
   // IntConnectedList.Add(4);

   // IntConnectedList.Add(5);

    // IntConnectedList.Remove(5);
    // IntConnectedList.Remove(4);
  //   IntConnectedList.Remove(2);


   // IntConnectedList.PrintAll();

cHTTP HTTP;
HTTP.LoadFromFile("http request.txt");

    return 0;
}
