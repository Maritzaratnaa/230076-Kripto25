'''
Nama        : Maritza Ratnamaya N
NPM         : 140810230076
Deskripsi   : Program enkripsi dan dekripsi Steganography dengan LSB
'''

from PIL import Image

# Konversi teks ke bit dan sebaliknya
def to_bits(text):
    return ''.join(format(ord(c), '08b') for c in text)

def from_bits(bits):
    chars = [chr(int(bits[i:i+8], 2)) for i in range(0, len(bits), 8)]
    return ''.join(chars)

# Encode
def encode(input_file, pesan, output_file):
    pesan += "###"  
    bits = to_bits(pesan)

    if input_file.lower().endswith(".png"):
        img = Image.open(input_file)
        encoded = img.copy()
        width, height = img.size

        idx = 0
        for y in range(height):
            for x in range(width):
                pixel = list(img.getpixel((x, y)))
                for n in range(3):
                    if idx < len(bits):
                        pixel[n] = (pixel[n] & ~1) | int(bits[idx])
                        idx += 1
                encoded.putpixel((x, y), tuple(pixel))
                if idx >= len(bits):
                    encoded.save(output_file, "PNG")
                    print(f"Pesan berhasil disisipkan ke '{output_file}'")
                    return
        print("Pesan terlalu panjang untuk file ini.")
        
    elif input_file.lower().endswith(".txt"):
        with open(input_file, "rb") as f:
            data = bytearray(f.read())

        if len(bits) > len(data):
            print("Pesan terlalu panjang untuk file ini.")
            return

        for i in range(len(bits)):
            data[i] = (data[i] & ~1) | int(bits[i])

        with open(output_file, "wb") as f:
            f.write(data)
        print(f"Pesan berhasil disisipkan ke '{output_file}'")
        
    else:
        print("Format file tidak didukung (hanya .png atau .txt).")

# Decode
def decode(input_file):
    bits = ""

    if input_file.lower().endswith(".png"):
        img = Image.open(input_file)
        width, height = img.size

        for y in range(height):
            for x in range(width):
                pixel = img.getpixel((x, y))
                for n in range(3):
                    bits += str(pixel[n] & 1)

    elif input_file.lower().endswith(".txt"):
        with open(input_file, "rb") as f:
            data = bytearray(f.read())
        bits = "".join(str(byte & 1) for byte in data)

    else:
        print("Format file tidak didukung (hanya .png atau .txt).")
        return

    decoded = from_bits(bits)
    end = decoded.find("###")
    if end != -1:
        print("Pesan tersembunyi:", decoded[:end])
    else:
        print("Tidak ada pesan tersembunyi.")

def main():
    while True:
        print("------- STEGANOGRAFI LSB -------")
        print("[HANYA UNTUK FILE .TXT DAN .PNG]")
        print("--------------------------------")
        print("1. Encode")
        print("2. Decode")
        print("3. Keluar")
        pilihan = input("=> ")
        print("\n--------------------------------")

        if pilihan == "1":
            input_file = input("Nama file input (.png /.txt): ")
            pesan = input("Pesan rahasia: ")
            output_file = input("Nama file output (.png /.txt): ")
            encode(input_file, pesan, output_file)
        elif pilihan == "2":
            input_file = input("Nama file (.png / .txt): ")
            decode(input_file)
        elif pilihan == "3":
            print("Program berhenti...")
            break
        else:
            print("Invalid.")

if __name__ == "__main__":
    main()
