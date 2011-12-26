#!/bin/bash
#
# A quick hack to compile PTAM (r114, 2010/01/29) on Ubuntu10.04LTS
# 
#    Many many thanks to Georg Klein
#                 and to Arnaud GROSJEAN
#
# 2010/10/19 Shorter script to "recompile only"
# 2010/10/12 Minor Bug Fixed, Patch of PTAM changed
# 2010/10/07 Released 
# 2010/10/02 start writing by Yoshinari Kameda, kameda[at]iit.tsukuba.ac.jp
#

targettopdir=$HOME/PTAM-work
pwdinfo=`pwd`

mkdir -p $targettopdir

# TooN
echo "------------------------------------"
echo "Start compiling Toon in 3 seconds..."
echo "------------------------------------"
sleep 3
pushd $targettopdir
cd TooN
make clean
./configure
sudo make install
popd

# libcvd
echo "--------------------------------------"
echo "Start compiling libcvd in 3 seconds..."
echo "--------------------------------------"
sleep 3
pushd $targettopdir
cd libcvd
make clean
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
cd gvars3
make clean
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
#unzip $pwdinfo/PTAM-r114-2010129.zip
#patch -p0 -d . < $pwdinfo/hack/PTAM/PTAM-r114-linux.patch
cd PTAM
make clean
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

