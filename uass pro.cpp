#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struktur untuk menyimpan data buku
struct Buku {
    string kode;
    string judul;
    string penulis;
    int stok;
    bool tersedia;
};

// Struktur untuk menyimpan data user
struct User {
    string username;
    string password;
    bool admin;
};

// Variabel global untuk menyimpan data
vector<Buku> daftarBuku;
vector<User> daftarUser;
User userSekarang;

// Fungsi untuk membersihkan layar
void bersihLayar() {
    system("cls");
}

// Fungsi untuk menampilkan header
void tampilkanHeader() {
    cout << "====================================\n";
    cout << "||      SISTEM PERPUSTAKAAN       ||\n";
    cout << "====================================\n";
}

// Fungsi untuk tambah buku (admin only)
void tambahBuku() {
    if(!userSekarang.admin) {
        cout << "\nAnda tidak memiliki akses!\n";
        system("pause");
        return;
    }

    bersihLayar();
    tampilkanHeader();

    Buku bukuBaru;
    cout << "\n--- TAMBAH BUKU BARU ---\n";

    // Input dan validasi kode buku
    cout << "Masukkan kode buku   : ";
    cin >> bukuBaru.kode;

    // Cek apakah kode buku sudah ada
    for(const Buku& buku : daftarBuku) {
        if(buku.kode == bukuBaru.kode) {
            cout << "\nKode buku sudah ada dalam sistem!\n";
            system("pause");
            return;
        }
    }

    cin.ignore();

    // Input dan validasi judul
    do {
        cout << "Masukkan judul buku  : ";
        getline(cin, bukuBaru.judul);
        if(bukuBaru.judul.empty()) {
            cout << "Judul buku tidak boleh kosong!\n";
        }
    } while(bukuBaru.judul.empty());

    // Input dan validasi penulis
    do {
        cout << "Masukkan nama penulis: ";
        getline(cin, bukuBaru.penulis);
        if(bukuBaru.penulis.empty()) {
            cout << "Nama penulis tidak boleh kosong!\n";
        }
    } while(bukuBaru.penulis.empty());

    // Input dan validasi stok
    do {
        cout << "Masukkan stok buku   : ";
        if(!(cin >> bukuBaru.stok) || bukuBaru.stok < 0) {
            cout << "Stok harus berupa angka positif!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            bukuBaru.stok = -1;
        }
    } while(bukuBaru.stok < 0);

    bukuBaru.tersedia = (bukuBaru.stok > 0);
    daftarBuku.push_back(bukuBaru);

    cout << "\nBuku berhasil ditambahkan!\n";
    cout << "\nDetail Buku yang Ditambahkan:";
    cout << "\nKode     : " << bukuBaru.kode;
    cout << "\nJudul    : " << bukuBaru.judul;
    cout << "\nPenulis  : " << bukuBaru.penulis;
    cout << "\nStok     : " << bukuBaru.stok;
    cout << "\nStatus   : " << (bukuBaru.tersedia ? "Tersedia" : "Tidak Tersedia") << endl;

    system("pause");
}

// Fungsi untuk registrasi user baru
void daftar() {
    bersihLayar();
    tampilkanHeader();

    User userBaru;
    cout << "\n--- DAFTAR USER BARU ---\n";

    cout << "Masukkan username: ";
    cin >> userBaru.username;

    // Cek apakah username sudah ada
    for(int i = 0; i < daftarUser.size(); i++) {
        if(daftarUser[i].username == userBaru.username) {
            cout << "\nUsername sudah digunakan!\n";
            system("pause");
            return;
        }
    }

    cout << "Masukkan password: ";
    cin >> userBaru.password;

    userBaru.admin = false; // User baru selalu bukan admin
    daftarUser.push_back(userBaru);

    cout << "\nPendaftaran berhasil!\n";
    system("pause");
}

// Fungsi untuk login
bool login() {
    bersihLayar();
    tampilkanHeader();

    string username, password;
    cout << "\n--- LOGIN ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for(int i = 0; i < daftarUser.size(); i++) {
        if(daftarUser[i].username == username && daftarUser[i].password == password) {
            userSekarang = daftarUser[i];
            return true;
        }
    }

    cout << "\nUsername atau password salah!\n";
    system("pause");
    return false;
}

// Fungsi untuk melihat daftar buku
void lihatBuku() {
    bersihLayar();
    tampilkanHeader();

    cout << "\n--- DAFTAR BUKU ---\n\n";
    cout << "No  Kode     Judul                    Penulis              Stok    Status\n";
    cout << "========================================================================\n";

    for(int i = 0; i < daftarBuku.size(); i++) {
        cout << i+1 << ".  ";
        cout << daftarBuku[i].kode << "      ";
        cout << daftarBuku[i].judul;
        // Mengatur spasi agar tampilan rapi
        for(int j = daftarBuku[i].judul.length(); j < 24; j++) cout << " ";
        cout << daftarBuku[i].penulis;
        for(int j = daftarBuku[i].penulis.length(); j < 20; j++) cout << " ";
        cout << daftarBuku[i].stok << "      ";
        cout << (daftarBuku[i].tersedia ? "Tersedia" : "Dipinjam") << endl;
    }

    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk meminjam buku
void pinjamBuku() {
    string kode;
    cout << "\n--- PINJAM BUKU ---\n";
    cout << "Masukkan kode buku: ";
    cin >> kode;

    for(int i = 0; i < daftarBuku.size(); i++) {
        if(daftarBuku[i].kode == kode) {
            if(daftarBuku[i].stok > 0 && daftarBuku[i].tersedia) {
                daftarBuku[i].stok--;
                if(daftarBuku[i].stok == 0) {
                    daftarBuku[i].tersedia = false;
                }
                cout << "\nBuku berhasil dipinjam!\n";
                system("pause");
                return;
            } else {
                cout << "\nBuku tidak tersedia!\n";
                system("pause");
                return;
            }
        }
    }

    cout << "\nBuku tidak ditemukan!\n";
    system("pause");
}

// Fungsi untuk mengembalikan buku
void kembalikanBuku() {
    string kode;
    cout << "\n--- KEMBALIKAN BUKU ---\n";
    cout << "Masukkan kode buku: ";
    cin >> kode;

    for(int i = 0; i < daftarBuku.size(); i++) {
        if(daftarBuku[i].kode == kode) {
            daftarBuku[i].stok++;
            daftarBuku[i].tersedia = true;
            cout << "\nBuku berhasil dikembalikan!\n";
            system("pause");
            return;
        }
    }

    cout << "\nBuku tidak ditemukan!\n";
    system("pause");
}

// Fungsi menu utama setelah login
void menuUtama() {
    int pilihan;
    do {
        bersihLayar();
        tampilkanHeader();

        cout << "\nSelamat datang, " << userSekarang.username << "!\n\n";
        cout << "MENU:\n";
        cout << "1. Lihat Daftar Buku\n";
        cout << "2. Pinjam Buku\n";
        cout << "3. Kembalikan Buku\n";
        if(userSekarang.admin) {
        cout << "4. Tambah Buku\n";
        }
        cout << "0. Logout\n";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                lihatBuku();
                break;
            case 2:
                pinjamBuku();
                break;
            case 3:
                kembalikanBuku();
                break;
            case 4:
                if(userSekarang.admin) {
                    tambahBuku();
                }
                break;
            case 0:
                cout << "\nLogout berhasil!\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }
    } while(pilihan != 0);
}

int main() {
    // Tambah admin default
    User admin = {"admin", "admin123", true};
    daftarUser.push_back(admin);

    int pilihan;
    do {
        bersihLayar();
        tampilkanHeader();

        cout << "\nMENU:\n";
        cout << "1. Login\n";
        cout << "2. Daftar\n";
        cout << "0. Keluar\n";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                if(login()) {
                    menuUtama();
                }
                break;
            case 2:
                daftar();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan sistem perpustakaan!\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }
    } while(pilihan != 0);

    return 0;
}
