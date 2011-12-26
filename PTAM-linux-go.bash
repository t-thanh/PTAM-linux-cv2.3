#!/bin/bash
#
# A quick hack to compile PTAM (r114, 2010/01/29) on Ubuntu10.04LTS
# 
#    Many many thanks to Georg Klein
#                 and to Arnaud GROSJEAN
#
# 2010/10/12 Minor Bug Fixed, Patch of PTAM changed
# 2010/10/07 Released 
# 2010/10/02 start writing by Yoshinari Kameda, kameda[at]iit.tsukuba.ac.jp
#

targettopdir=$HOME/PTAM-work
pwdinfo=`pwd`

# OpenCV?
echo "--------------------------------------------------------------"
echo "Do you have OpenCV 2.1.0 ? If not, stop here and prepare that."
echo "(Pausing 10 seconds here)"
echo "--------------------------------------------------------------"
sleep 10

# You may need more?
# Consult "Ubuntu10.04LTS + OpenCV2.1.0 on USB" project by kameda 
echo "----------------------------------------------------------"
echo "You need liblapack-dev freeglut3-dev, and libdc1394-22-dev"
echo "Are you OK? (Pausing 10 seconds here)"
echo "-----------------------------------------------------------"
sleep 10
sudo apt-get install liblapack-dev freeglut3-dev libdc1394-22-dev

export CVS_RSH=ssh

mkdir -p $targettopdir

# TooN
echo "------------------------------------"
echo "Start compiling Toon in 3 seconds..."
echo "------------------------------------"
sleep 3
pushd $targettopdir
cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/toon co -D "Mon May 11 16:29:26 BST 2009" TooN
cd TooN
./configure
sudo make install
popd

# libcvd
echo "--------------------------------------"
echo "Start compiling libcvd in 3 seconds..."
echo "--------------------------------------"
sleep 3
pushd $targettopdir
cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/libcvd co -D "Mon May 11 16:29:26 BST 2009" libcvd
cd libcvd
mv cvd_src/convolution.cc cvd_src/convolution.cc-original
cp $pwdinfo/hack/libcvd/convolution.cc cvd_src/convolution.cc
export CXXFLAGS=-D_REENTRANT
./configure --without-ffmpeg
make
sudo make install
popd

# gvars3
echo "---------------------------------------"
echo "Start compiling gvars3 in 3 seconds ..."
echo "---------------------------------------"
sleep 3
pushd $targettopdir
cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/libcvd co -D "Mon May 11 16:29:26 BST 2009" gvars3
cd gvars3
mv gvars3/serialize.h gvars3/serialize.h-original
cp $pwdinfo/hack/gvars3/serialize.h gvars3/serialize.h
./configure --disable-widgets
make
sudo make install
popd

# before you go further, re-arrange the dynamic libraries
sudo ldconfig

# PTAM main
echo "--------------------------------------"
echo "Start compiling PTAM in 10 seconds ..."
echo "YOU NEED TO AGREE WITH THEIR LICENSE !"
echo "--------------------------------------"
sleep 10
pushd $targettopdir
unzip $pwdinfo/PTAM-r114-2010129.zip
patch -p0 -d . < $pwdinfo/hack/PTAM/PTAM-r114-linux.patch
cd PTAM
cp Build/Linux/* .
make

# Tips at end
echo "----------------"
echo "Is the camera ready?"
echo "Let's go to $HOME/PTAM-work/PTAM "
echo "You need to first run ./CameraCalibrator"
echo "and save a camera config file."
echo "Then, you can enjoy ./PTAM !"
echo "----------------"

exit 0

