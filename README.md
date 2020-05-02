# CheaterHub

A portable software for lovely cheaters, C++ Back-end, with Qt Front-end, self-practice project.

A simple customized asynchronous TCP for Back-end, by using multi-threading.

Implemented game(s):

+ Wordscapes

## Run

### Qt Front-end

Located in `client/CheateHub`, build it, and config Back-end ip and port information at Config session in the application.

### Back-end

Build by running `make` from `server/` directory, `make MODE=release` for releasing. Executable file will locate in `server/build/`.

#### Wordscapes

Module locate in `server/wordscapes/`.

For first time, have to generate dictionary before running, by using script `server/tools/generateDict.py`.

For testing this module individually, build by running `make test`.

## TODO

Add config feature for back-end.

Makefile for server could be improved.

Message format for communicating between front-end and back-end could be improved, especially when implemented more games.
