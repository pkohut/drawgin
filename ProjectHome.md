## DrawGin ##
Using published file format specifications for ".dwg" files, create a support library to read and write those file types.

Current work will focus on the AC1012-AC1015 file formats, with AC1018 following shortly thereafter. Support for newer formats will be added as their file structures are discovered and publicly made available to the public.

### Current Status ###
  * [Implementation status](Feature_Status.md) of the .dwg format can be found on the [DrawGin Wiki](http://code.google.com/p/drawgin/w/list). The most current version of the list can be found in the file feature\_status.txt.
  * The project is at the very beginning stages of development and does not have a stable API or library.

### Project Dependencies ###
Visual Studio 2012 or higher. You can get the express edition for free from Microsoft.<br>
<a href='http://code.google.com/p/google-glog/'>Google GLog</a><br>

<h3>Compiling</h3>
A VS 2012 solution is provided for MSVS users. The previous cmake options have been temorarily removed. This means there is no easy way to build from Xcode or linux.<br>
