{ pkgs? import <nixpkgs> {} }:
pkgs.mkShell {
  nativeBuildInputs = [
    pkgs.gcc
    pkgs.glibc
    pkgs.libcxx
    pkgs.lld
    pkgs.gdb
    pkgs.libpng
    pkgs.libjpeg
    # pkgs.libxxf86vm1
    # pkgs.libxxf86vm
    # pkgs.libxi
    # pkgs.libxrandr
    pkgs.mesa
    pkgs.mesa.drivers
    pkgs.cmake
    pkgs.gnumake
  ];
  shellHook = ''
    export LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";
  '';
}
