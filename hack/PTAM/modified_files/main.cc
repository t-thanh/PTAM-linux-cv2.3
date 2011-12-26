// Copyright 2008 Isis Innovation Limited
// This is the main extry point for PTAM
#include <stdlib.h>
#include <iostream>
#include <gvars3/instances.h>
#include "System.h"


using namespace std;
using namespace GVars3;

// 2010/10/06 kameda[at]iit.tsukuba.ac.jp
// To hand over the camera name
bool kmd_coloron = false;
bool kmd_lighton = true;
string kmd_cameraname = "";

// 2010/10/06 kameda[at]iit.tsukuba.ac.jp
// Parsing command-line options
void kmd_parseoptions(int argc, char *argv[]) 
{
  int i = 0;
  cout << "  KMD: parsing command line options ... " << endl;

  for (i = 1; i < argc; i++) {
    // cout << i << " " << argv[i] << endl;
    if (string(argv[i]) == "-coloron") {
      kmd_coloron = true;
      cout << "  KMD: -coloron: Always show color images" << endl;
      cout << "                 (to overccome the case GL_LUMINANCE does not work) ..." << endl;
    } else if (string(argv[i]) == "-lightoff") {
      kmd_lighton = false;
      cout << "  KMD: -lightoff: Light turned off to avoid black eyes..." << endl;
    } else {
      kmd_cameraname = string(argv[i]);
      cout << "  KMD: Camera-name is now set to \"" << kmd_cameraname << "\"" << endl;
    }
  }
  return;
}

int main(int argc, char *argv[])
{
  cout << "  Welcome to PTAM " << endl;
  cout << "  --------------- " << endl;
  cout << "  Parallel tracking and mapping for Small AR workspaces" << endl;
  cout << "  Copyright (C) Isis Innovation Limited 2008 " << endl;  
  cout << endl;

  // 2010/10/06 kameda[at]iit.tsukuba.ac.jp
  cout << "  | You may try these options at command line (by Y.Kameda, 2010/10)" << endl;
  cout << "  |   -coloron  ... If you unfortunately see black image, try this" << endl;
  cout << "  |   -lightoff ... If you want to avoid black eye-balls, try this" << endl;
  cout << "  |    0        ... Select 1st USB camera" << endl;
  cout << "  |    1        ... Select 2nd USB camera (and 2 for 3rd, ...) " << endl;
  cout << endl;  
  kmd_parseoptions(argc, argv);
  
  cout << "  Parsing settings.cfg ...." << endl;
  GUI.LoadFile("settings.cfg");
  GUI.StartParserThread(); // Start parsing of the console input
  atexit(GUI.StopParserThread); 

  try
    {
      System s;
      s.Run();
    }
  catch(CVD::Exceptions::All e)
    {
      cout << endl;
      cout << "!! Failed to run system; got exception. " << endl;
      cout << "   Exception was: " << endl;
      cout << e.what << endl;
    }
}










