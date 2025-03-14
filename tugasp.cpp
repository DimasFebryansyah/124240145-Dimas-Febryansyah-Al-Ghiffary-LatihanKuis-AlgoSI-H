#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Buku
{
    char id[50];
    char judul[100];
    char penulis[100];
    int stok;
};

Buku buku[100];
int jumlahBuku = 0;
void bersihkan()
{
    char pilihan;
    cout << "Balik ke menu? (Y/N)\n";
    cin >> pilihan;
    cin.ignore();
    if (pilihan == 'y' || pilihan == 'Y')
    {
        system("cls");
    }
}
void muatBuku()
{
    FILE *file = fopen("data.dat", "r");
    if (file != nullptr)
    {
        while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", buku[jumlahBuku].id, buku[jumlahBuku].judul, buku[jumlahBuku].penulis, &buku[jumlahBuku].stok) != EOF)
        {
            ++jumlahBuku;
        }
        fclose(file);
    }
    else
    {
        cerr << "Silahkan login dahulu\n";
    }
}

void simpanBuku()
{
    FILE *file = fopen("data.dat", "w");
    if (file != nullptr)
    {
        for (int i = 0; i < jumlahBuku; ++i)
        {
            fprintf(file, "%s,%s,%s,%d\n", buku[i].id, buku[i].judul, buku[i].penulis, buku[i].stok);
        }
        fclose(file);
    }
    else
    {
        cerr << "Kesalahan saat membuka file untuk menulis.\n";
    }
}

void login()
{
    char username[50], password[50];
    cout << "Login\n";
    while (true)
    {
        cout << "Username: ";
        cin.getline(username, 50);
        cout << "Password: ";
        cin.getline(password, 50);
        if (strcmp(username, "dimas") == 0 && strcmp(password, "145") == 0)
        {
            cout << "Login berhasil!\n";
            break;
        }
        else
        {
            cout << "Kredensial tidak valid. Coba lagi.\n";
        }
    }
}

void tambahBuku()
{
    Buku book;
    cout << "Masukkan ID buku: ";
    cin.getline(book.id, 50);
    cout << "Masukkan judul buku: ";
    cin.getline(book.judul, 100);
    cout << "Masukkan penulis buku: ";
    cin.getline(book.penulis, 100);
    cout << "Masukkan stok buku: ";
    cin >> book.stok;
    cin.ignore();
    if (strlen(book.id) == 0 || strlen(book.judul) == 0 || strlen(book.penulis) == 0 || book.stok <= 0)
    {
        cout << "Input tidak valid. Silakan masukkan semua detail dengan benar.\n";
        return;
    }
    buku[jumlahBuku++] = book;
    cout << "Buku berhasil ditambahkan.\n";
    bersihkan();
}
void cariBuku()
{
    char keyword[100];
    cout << "Masukkan kata kunci judul untuk mencari: ";
    cin.getline(keyword, 100);
    bool found = false;

    for (int i = 0; i < jumlahBuku; ++i)
    {
        if (strstr(buku[i].judul, keyword))
        {
            if (!found)
            {
                cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
                cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
                found = true;
            }
            cout << left << setw(10) << buku[i].id << setw(30) << buku[i].judul << setw(30) << buku[i].penulis << setw(10) << buku[i].stok << endl;
        }
    }

    if (!found)
    {
        cout << "Buku dengan judul \"" << keyword << "\" tidak ditemukan.\n";
    }

    bersihkan(); // Clear the screen at the end
}

void hapusBuku()
{
    char id[50];
    cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
    cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
    for (int i = 0; i < jumlahBuku; ++i)
    {
        cout << left << setw(10) << buku[i].id << setw(30) << buku[i].judul << setw(30) << buku[i].penulis << setw(10) << buku[i].stok << endl;
    }
    cout << "Masukkan ID buku untuk dihapus: ";
    cin.getline(id, 50);
    bool found = false;
    for (int i = 0; i < jumlahBuku; ++i)
    {
        if (strcmp(buku[i].id, id) == 0)
        {
            for (int j = i; j < jumlahBuku - 1; ++j)
            {
                buku[j] = buku[j + 1];
            }
            --jumlahBuku;
            found = true;
            break; // Exit loop after deleting the book
        }
    }

    if (found)
    {
        cout << "Buku dengan ID " << id << " berhasil dihapus.\n";

        // Display updated table
        cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
        cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
        for (int i = 0; i < jumlahBuku; ++i)
        {
            cout << left << setw(10) << buku[i].id << setw(30) << buku[i].judul << setw(30) << buku[i].penulis << setw(10) << buku[i].stok << endl;
        }
    }
    else
    {
        cout << "Buku tidak ditemukan.\n";
    }

    bersihkan(); // Clear the screen at the end
}

bool bandingkanId(const Buku &a, const Buku &b)
{
    return strcmp(a.id, b.id) < 0;
}

void bubbleSort()
{
    bool swapped;
    for (int i = 0; i < jumlahBuku - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < jumlahBuku - i - 1; ++j)
        {
            if (!bandingkanId(buku[j], buku[j + 1]))
            {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
void tampilkanBuku()
{
    if (jumlahBuku == 0)
    {
        cout << "Belum ada buku yang dimasukkan.";
        cout << endl;
        bersihkan();
    }
    else
    {
        bubbleSort();
        cout << "Daftar Buku:\n";
        cout << left << setw(10) << "ID" << setw(30) << "Judul" << setw(30) << "Penulis" << setw(10) << "Stok" << endl;
        cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
        for (int i = 0; i < jumlahBuku; ++i)
        {
            cout << left << setw(10) << buku[i].id << setw(30) << buku[i].judul << setw(30) << buku[i].penulis << setw(10) << buku[i].stok << endl;
        }
        bersihkan();
    }
}

int main()
{
    muatBuku();
    login();
    int pilihan;
    do
    {
        cout << "1. Tambah Buku\n2. Tampilkan Buku\n3. Cari Buku\n4. Hapus Buku\n5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilkanBuku();
            break;
        case 3:
            cariBuku();
            break;
        case 4:
            hapusBuku();
            break;
        case 5:
            simpanBuku();
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 5);
    return 0;
}
