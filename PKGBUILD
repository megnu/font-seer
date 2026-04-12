pkgname=font-seer
pkgver=$(<VERSION)
pkgrel=1
pkgdesc="GTK3 font preview and metadata viewer"
arch=('x86_64')
license=('GPL-2.0-or-later')
depends=('gtk3' 'fontconfig' 'pango')
makedepends=('pkg-config' 'gcc' 'make')
source=('VERSION' 'font_seer.c' 'Makefile' 'font-seer.png' 'font-seer.desktop' 'README.md' 'LICENSE')
md5sums=('1347633cdf7cdcb2168d61093630d5ae'
         '64b37d9dd293dc458f945351edb52a2f'
         '7b229262d017e8f6971f21945fe2ce27'
         'c03a941223360edfaf9adc5713a98c51'
         'd3b41f0bbc404fd74f146ecef34fc974'
         '5acbcbd9625c0911289484a26d23bbd2'
         'cf370a5ad92d905c270a6031f24db592')

build() {
  cd "$srcdir"
  make
}

package() {
  cd "$srcdir"
  install -Dm755 font_seer "$pkgdir/usr/bin/font-seer"
  install -Dm644 font-seer.png "$pkgdir/usr/share/pixmaps/font-seer.png"
  install -Dm644 font-seer.desktop "$pkgdir/usr/share/applications/font-seer.desktop"
  install -Dm644 README.md "$pkgdir/usr/share/doc/font-seer/README.md"
  install -Dm644 LICENSE "$pkgdir/usr/share/licenses/font-seer/LICENSE"
}
