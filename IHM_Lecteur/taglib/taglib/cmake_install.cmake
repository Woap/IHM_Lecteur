# Install script for directory: /home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libtag.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/libtag.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/taglib/tag.h;/usr/local/include/taglib/fileref.h;/usr/local/include/taglib/audioproperties.h;/usr/local/include/taglib/taglib_export.h;/usr/local/include/taglib/taglib_config.h;/usr/local/include/taglib/taglib.h;/usr/local/include/taglib/tstring.h;/usr/local/include/taglib/tlist.h;/usr/local/include/taglib/tlist.tcc;/usr/local/include/taglib/tstringlist.h;/usr/local/include/taglib/tbytevector.h;/usr/local/include/taglib/tbytevectorlist.h;/usr/local/include/taglib/tbytevectorstream.h;/usr/local/include/taglib/tiostream.h;/usr/local/include/taglib/tfile.h;/usr/local/include/taglib/tfilestream.h;/usr/local/include/taglib/tmap.h;/usr/local/include/taglib/tmap.tcc;/usr/local/include/taglib/tpropertymap.h;/usr/local/include/taglib/trefcounter.h;/usr/local/include/taglib/tdebuglistener.h;/usr/local/include/taglib/mpegfile.h;/usr/local/include/taglib/mpegproperties.h;/usr/local/include/taglib/mpegheader.h;/usr/local/include/taglib/xingheader.h;/usr/local/include/taglib/id3v1tag.h;/usr/local/include/taglib/id3v1genres.h;/usr/local/include/taglib/id3v2extendedheader.h;/usr/local/include/taglib/id3v2frame.h;/usr/local/include/taglib/id3v2header.h;/usr/local/include/taglib/id3v2synchdata.h;/usr/local/include/taglib/id3v2footer.h;/usr/local/include/taglib/id3v2framefactory.h;/usr/local/include/taglib/id3v2tag.h;/usr/local/include/taglib/attachedpictureframe.h;/usr/local/include/taglib/commentsframe.h;/usr/local/include/taglib/eventtimingcodesframe.h;/usr/local/include/taglib/generalencapsulatedobjectframe.h;/usr/local/include/taglib/ownershipframe.h;/usr/local/include/taglib/popularimeterframe.h;/usr/local/include/taglib/privateframe.h;/usr/local/include/taglib/relativevolumeframe.h;/usr/local/include/taglib/synchronizedlyricsframe.h;/usr/local/include/taglib/textidentificationframe.h;/usr/local/include/taglib/uniquefileidentifierframe.h;/usr/local/include/taglib/unknownframe.h;/usr/local/include/taglib/unsynchronizedlyricsframe.h;/usr/local/include/taglib/urllinkframe.h;/usr/local/include/taglib/chapterframe.h;/usr/local/include/taglib/tableofcontentsframe.h;/usr/local/include/taglib/podcastframe.h;/usr/local/include/taglib/oggfile.h;/usr/local/include/taglib/oggpage.h;/usr/local/include/taglib/oggpageheader.h;/usr/local/include/taglib/xiphcomment.h;/usr/local/include/taglib/vorbisfile.h;/usr/local/include/taglib/vorbisproperties.h;/usr/local/include/taglib/oggflacfile.h;/usr/local/include/taglib/speexfile.h;/usr/local/include/taglib/speexproperties.h;/usr/local/include/taglib/opusfile.h;/usr/local/include/taglib/opusproperties.h;/usr/local/include/taglib/flacfile.h;/usr/local/include/taglib/flacpicture.h;/usr/local/include/taglib/flacproperties.h;/usr/local/include/taglib/flacmetadatablock.h;/usr/local/include/taglib/apefile.h;/usr/local/include/taglib/apeproperties.h;/usr/local/include/taglib/apetag.h;/usr/local/include/taglib/apefooter.h;/usr/local/include/taglib/apeitem.h;/usr/local/include/taglib/mpcfile.h;/usr/local/include/taglib/mpcproperties.h;/usr/local/include/taglib/wavpackfile.h;/usr/local/include/taglib/wavpackproperties.h;/usr/local/include/taglib/trueaudiofile.h;/usr/local/include/taglib/trueaudioproperties.h;/usr/local/include/taglib/rifffile.h;/usr/local/include/taglib/aifffile.h;/usr/local/include/taglib/aiffproperties.h;/usr/local/include/taglib/wavfile.h;/usr/local/include/taglib/wavproperties.h;/usr/local/include/taglib/infotag.h;/usr/local/include/taglib/asffile.h;/usr/local/include/taglib/asfproperties.h;/usr/local/include/taglib/asftag.h;/usr/local/include/taglib/asfattribute.h;/usr/local/include/taglib/asfpicture.h;/usr/local/include/taglib/mp4file.h;/usr/local/include/taglib/mp4atom.h;/usr/local/include/taglib/mp4tag.h;/usr/local/include/taglib/mp4item.h;/usr/local/include/taglib/mp4properties.h;/usr/local/include/taglib/mp4coverart.h;/usr/local/include/taglib/modfilebase.h;/usr/local/include/taglib/modfile.h;/usr/local/include/taglib/modtag.h;/usr/local/include/taglib/modproperties.h;/usr/local/include/taglib/itfile.h;/usr/local/include/taglib/itproperties.h;/usr/local/include/taglib/s3mfile.h;/usr/local/include/taglib/s3mproperties.h;/usr/local/include/taglib/xmfile.h;/usr/local/include/taglib/xmproperties.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/taglib" TYPE FILE FILES
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/tag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/fileref.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/audioproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/taglib_export.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/../taglib_config.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/taglib.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tstring.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tlist.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tlist.tcc"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tstringlist.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tbytevector.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tbytevectorlist.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tbytevectorstream.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tiostream.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tfilestream.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tmap.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tmap.tcc"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tpropertymap.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/trefcounter.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/toolkit/tdebuglistener.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/mpegfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/mpegproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/mpegheader.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/xingheader.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v1/id3v1tag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v1/id3v1genres.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2extendedheader.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2frame.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2header.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2synchdata.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2footer.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2framefactory.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/id3v2tag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/commentsframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/ownershipframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/popularimeterframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/privateframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/relativevolumeframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/textidentificationframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/unknownframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/urllinkframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/chapterframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/tableofcontentsframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpeg/id3v2/frames/podcastframe.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/oggfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/oggpage.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/oggpageheader.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/xiphcomment.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/vorbis/vorbisfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/vorbis/vorbisproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/flac/oggflacfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/speex/speexfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/speex/speexproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/opus/opusfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ogg/opus/opusproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/flac/flacfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/flac/flacpicture.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/flac/flacproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/flac/flacmetadatablock.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ape/apefile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ape/apeproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ape/apetag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ape/apefooter.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/ape/apeitem.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpc/mpcfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mpc/mpcproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/wavpack/wavpackfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/wavpack/wavpackproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/trueaudio/trueaudiofile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/trueaudio/trueaudioproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/rifffile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/aiff/aifffile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/aiff/aiffproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/wav/wavfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/wav/wavproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/riff/wav/infotag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/asf/asffile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/asf/asfproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/asf/asftag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/asf/asfattribute.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/asf/asfpicture.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4file.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4atom.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4tag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4item.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4properties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mp4/mp4coverart.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mod/modfilebase.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mod/modfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mod/modtag.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/mod/modproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/it/itfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/it/itproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/s3m/s3mfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/s3m/s3mproperties.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/xm/xmfile.h"
    "/home/yanis/Bureau/IHM_Lecteur/IHM_Lecteur/taglib/taglib/xm/xmproperties.h"
    )
endif()

