===Project Dependencies===
[http://www.boost.com Boost C++ Library]<br>
[http://code.google.com/p/google-glog/ Google GLog]

See the file 'Dependencies.txt' for information about building and installing
required dependencies for Linux - OS X - Windows


===Compiling===
TODO:

===Debugging===
In VS, add the following to Debugging/Command Arguments section of DrawginApp property page:
--v=4 --log_dir=$(OutDir)\logs --alsologtostderr=1 --drawing=C:\Users\Paul\Documents\TestDwgs\TestDwg3.dwg