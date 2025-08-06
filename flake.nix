{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    SDL2
    pkg-config
    cpplint
  ];
}
