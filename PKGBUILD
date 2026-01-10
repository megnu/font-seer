pkgname=font-seer
pkgver=0.1
pkgrel=1
pkgdesc="GTK3 font metadata viewer"
arch=('x86_64')
license=('custom')
depends=('gtk3' 'fontconfig' 'pango')
makedepends=('pkg-config' 'gcc' 'make')
source=('font_seer.c' 'Makefile' 'font-seer.png' 'font-seer.desktop')
md5sums=('64b37d9dd293dc458f945351edb52a2f'
         '7b229262d017e8f6971f21945fe2ce27'
         '2a9c9fad25d86102113728692ad9df37'
         'd3b41f0bbc404fd74f146ecef34fc974')

build() {
  cd "$srcdir"
  make
}

package() {
  cd "$srcdir"
  install -Dm755 font_seer "$pkgdir/usr/bin/font-seer"
  install -Dm644 font-seer.png "$pkgdir/usr/share/pixmaps/font-seer.png"
  install -Dm644 font-seer.desktop "$pkgdir/usr/share/applications/font-seer.desktop"
}
