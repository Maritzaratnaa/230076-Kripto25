'''
Nama        : Maritza Ratnamaya N
NPM         : 140810230076
Deskripsi   : Program enkripsi dan dekripsi menggunakan algoritma ElGamal
'''

def mod_pow(base, exp, mod):
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp //= 2
        base = (base * base) % mod
    return result

def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    if m == 1:
        return 0
    while a > 1:
        q = a // m
        a, m = m, a % m
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += m0
    return x1

# Proses awal enkripsi
def encrypt_num(m, p, g, x, k):
    y = mod_pow(g, x, p)            # y = g^x mod p
    a = mod_pow(g, k, p)            # a = g^k mod p
    b = (m * mod_pow(y, k, p)) % p  # b = (m * y^k) mod p
    return (a, b)

# Proses awal dekripsi
def decrypt_num(a, b, p, x):
    c = mod_pow(a, x, p)        # c = a^x mod p
    c_inv = mod_inverse(c, p)   # c_inv = c^(-1) mod p
    m = (b * c_inv) % p         # m = (b * c_inv) mod p
    return m

# Konversi huruf kapital ke angka 0–25
def char_to_num(ch):
    return ord(ch) - 65 

# Konversi angka 0–25 ke huruf kapital
def num_to_char(n):
    return chr(n + 65)

# Enkripsi string huruf
def encrypt_text(text, p, g, x, k):
    ct = []
    for ch in text:
        m = char_to_num(ch)
        a, b = encrypt_num(m, p, g, x, k)
        ct.append((a, b))
    return ct

# Dekripsi list ciphertext menjadi string
def decrypt_text(ct, p, x):
    pt = ""
    for a, b in ct:
        m = decrypt_num(a, b, p, x)
        pt += num_to_char(m)
    return pt

def main():
    while True:
        print("\n------ Algoritma ElGamal ------")
        print("1. Enkripsi")
        print("2. Dekripsi")
        print("0. Keluar")
        choice = input("=> ")

        if choice == "1":
            print("\n--- Enkripsi ---")
            p = int(input("p (prima > 25): "))
            g = int(input("g (generator): "))
            x = int(input("private key x: "))
            k = int(input("k (k < p): "))
            text = input("Plaintext (KAPITAL): ")

            ct = encrypt_text(text, p, g, x, k)
            print("\nCiphertext: ")
            print(ct)

        elif choice == "2":
            print("\n--- Dekripsi ---")
            p = int(input("p (prima > 25): "))
            x = int(input("private key x: "))
            print("Pasangan ciphertext dipisah koma, contoh: 11 2, 11 23")
            raw = input("Ciphertext: ")

            ct = []
            for pair in raw.split(","):
                a, b = map(int, pair.strip().split())
                ct.append((a, b))

            pt = decrypt_text(ct, p, x)
            print("\nPlaintext: ", pt)

        elif choice == "0":
            break
        else:
            print("Pilihan tidak valid!")

if __name__ == "__main__":
    main()
