@echo off
cpplint --filter=-legal --exclude=src/lib --recursive src/

set OR_FLAG=FALSE
set NO_CONF="--no-conf"
IF "%1"==%NO_CONF% set OR_FLAG=TRUE
IF "%2"==%NO_CONF% set OR_FLAG=TRUE
IF NOT %OR_FLAG%==TRUE cmake . -B build > nul

set OR_FLAG=FALSE
set NO_MSG="--no-msg"
IF "%1"==%NO_MSG% set OR_FLAG=TRUE
IF "%2"==%NO_MSG% set OR_FLAG=TRUE
IF NOT %OR_FLAG%==TRUE (
  cmake --build build
) ELSE (
  cmake --build build > nul
)