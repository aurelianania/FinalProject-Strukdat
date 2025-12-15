Simulasi Bola Memantul
Bruteforce & Quadtree (graphics.h – C++)

Program ini merupakan simulasi beberapa bola yang bergerak dan memantul di dalam layar menggunakan library graphics.h.  
Setiap bola dapat bertabrakan dengan bola lain, dan program ini memiliki dua metode deteksi tabrakan:

- Bruteforce
- Quadtree

Kita dapat berpindah mode dengan menekan tombol spasi.


Struktur Program

1. Class Ball
   Atribut:
- x, y (posisi bola)
- vx, vy (kecepatan bola)
- r (radius bola)
- color (warna bola)

Metode:
- update(), untuk menggerakkan bola dan memantulkan dari dinding
- draw(),  untuk menggambar bola ke layar

2. Fungsi collision(Ball &a, Ball &b)
   Cara kerja:
- Menghitung jarak antar pusat bola
- Jika jarak lebih kecil dari jumlah radius, maka terjadi tabrakan
- Kecepatan kedua bola ditukar untuk menggambarkan pantulan

3. Bruteforce Collision Detection
   Semua pasangan bola dicek satu per satu menggunakan dua nested loop.
   Ciri:
- Mudah diimplementasikan
- Kompleksitas waktu O(n²)
- Tidak efisien untuk jumlah bola besar

4. Class Quadtree
   Digunakan untuk optimasi collision detection dengan membagi ruang menjadi beberapa area (node).
   Fungsi utama:
- Menyimpan bola dalam struktur pohon berdasarkan posisi
- Mengurangi jumlah pasangan bola yang perlu dicek
Pada program ini, Quadtree digunakan sebagai konsep pembagian ruang dan dapat diaktifkan dengan tombol spasi

Cara Menjalankan Program:
1. Pastikan compiler mendukung graphics.h
2. Compile program C++
3. Jalankan executable
4. Tekan spasi untuk berpindah mode collision
