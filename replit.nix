{ pkgs }: {
	deps = [
		pkgs.minio-client
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}