pkgname=font-seer
pkgver=$(<VERSION)
pkgrel=1
pkgdesc="GTK3 font preview and metadata viewer"
arch=('x86_64')
license=('GPL-2.0-or-later')
depends=('gtk3' 'fontconfig' 'pango')
makedepends=('pkg-config' 'gcc' 'make')
source=('VERSION' 'main.c' 'Makefile' 'font-seer.png' 'font-seer.desktop' 'README.md' 'LICENSE')
md5sums=('c9e47dbb0e1927076ed7b2e1ec157be7'
         '4c9dc735f36f4898fa09bf798fd29d05'
         '82d15ed78949ef7ff833db9797523a21'
         '82e32043e32477f0ba29a306a150b4be'
         'd3b41f0bbc404fd74f146ecef34fc974'
         '32bd98838ac5c5c3903a552a0a3acf56'
         '25c7d05590dacead9a79e91e7d39f2cb')

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
