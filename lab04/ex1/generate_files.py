import struct
import random
import os

def generate_binary_dataset(directory, n):
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"Created directory: {directory}")

    for i in range(1, n + 1):
        fname = f"f{i}.bin"
        path = os.path.join(directory, fname)
        count = random.randint(500000, 1000000)
        print(f"Generating {path} ({count} elements)...")

        with open(path, 'wb') as f:
            f.write(struct.pack('i', count))

            chunk_size = 100000
            written = 0
            while written < count:
                current_chunk = min(chunk_size, count - written)
                data = [random.randint(-1000000, 1000000) for _ in range(current_chunk)]
                f.write(struct.pack(f'{current_chunk}i', *data))
                written += current_chunk

        print(f"Finished {fname}")

if __name__ == "__main__":
    target_dir = "./files/"
    n = 20

    generate_binary_dataset(target_dir, n)
    print("\nAll files generated successfully.")