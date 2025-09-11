{
  #source : https://nixcademy.com/posts/cpp-with-nix-in-2023-part-1-shell/
  description = "Nix flake for C++ snake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
      ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gcc
            clang-tools
            bear
            SDL2
            SDL2_ttf
            pkg-config
            cpplint
          ];
        };
      };
    };
}