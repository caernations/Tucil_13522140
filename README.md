# IF2211 STRATEGI ALGORITMA
Tugas Kecil 1 Strategi Algoritma


## IDENTITAS
| Nama | NIM |
| ----------- | ----------- |
| Yasmin Farisah Salma | 13521007 |

## DESKRIPSI PROGRAM
Cyberpunk 2077 Breach Protocol adalah minigame meretas pada permainan video Cyberpunk 2077. Minigame ini merupakan simulasi peretasan jaringan local dari ICE (Intrusion Countermeasures Electronics) pada permainan Cyberpunk 2077. Komponen pada permainan ini antara lain adalah:

1. `Token` – terdiri dari dua karakter alfanumerik seperti E9, BD, dan 55.
2. `Matriks` – terdiri atas token-token yang akan dipilih untuk menyusun urutan kode.
3. `Sekuens`  – sebuah rangkaian token (dua atau lebih) yang harus dicocokkan.
4. `Buffer` – jumlah maksimal token yang dapat disusun secara sekuensial.

### ATURAN PERMAINAN
1. Pemain bergerak dengan pola horizontal, vertikal, horizontal, vertikal (bergantian) hingga
semua sekuens berhasil dicocokkan atau buffer penuh.
2. Pemain memulai dengan memilih satu token pada posisi baris paling atas dari matriks.
3. Sekuens dicocokkan pada token-token yang berada di buffer.
4. Satu token pada buffer dapat digunakan pada lebih dari satu sekuens.
5. Setiap sekuens memiliki bobot hadiah atau reward yang variatif.
6. Sekuens memiliki panjang minimal berupa dua token.

## COMPILE & RUN PROGRAM

Make sure that you're in the right directory

### Change Directory

Go to 'source' directory

```bash
cd source
```

### Compile

Open terminal compile the program

```bash
g++ main.cpp -o main
```

### Run

```bash
./main
```

## SPESIFIKASI TUGAS
| Poin                           |   Ya    |                                         Tidak                                                   |
| ------------------------------ | :------: | :-----------------------------------------------------------------------------------------------------------------: |
| Program berhasil dikompilasi tanpa kesalahan | ✓ | |
| Program berhasil dijalankan  |  ✓ ||
| Program dapat membaca masukan berkas .txt | ✓ ||
| Program dapat menghasilkan masukan secara acak | ✓ ||
| Solusi yang diberikan program optimal | ✓ ||
| Program dapat menyimpan solusi dalam berkas .txt | ✓ ||
| Program memiliki GUI || ✓ |