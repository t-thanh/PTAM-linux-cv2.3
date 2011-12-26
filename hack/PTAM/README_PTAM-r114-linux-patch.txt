2010/10/13 kameda[at]iit.tsukuba.ac.jp
2010/10/07 kameda[at]iit.tsukuba.ac.jp

PTAM-r114-linux.patch should be applied after you copy Build/Linux/*.

$ unzip PTAM.zip
$ patch -p0 -d . < PTAM-r114-linux.patch
$ cd PTAM
$ cp Build/Linux/* .
$ make

Then,

$ ./CameraCalibrator
$ ./PTAM

or

$ ./CameraCalibrator -coloron
$ ./PTAM -coloron -lightoff

or with camera-1, 

$ ./CameraCalibrator 1
$ ./PTAM 1

---end---

