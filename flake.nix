{
  description = "A flake to build a C++ project with Google Benchmark";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable"; # Use a recent version of nixpkgs
  };

  outputs = { self, nixpkgs }: {
    packages.default = nixpkgs.lib.mkShell {
      buildInputs = [
        nixpkgs.gbenchmark
        nixpkgs.gtest
        nixpkgs.cmake
        nixpkgs.gcc
      ];
    };

    # Optional: A devShell to provide a shell environment
    devShell = nixpkgs.mkShell {
      buildInputs = [
        nixpkgs.gbenchmark
        nixpkgs.gtest
        nixpkgs.cmake
        nixpkgs.gcc
      ];
    };
  };
}
