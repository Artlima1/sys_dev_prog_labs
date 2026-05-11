import struct
import random
import os

def generate_binary_dataset(directory, filenames, count_per_file):
    # Ensure the directory exists
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"Created directory: {directory}")

    for fname in filenames:
        path = os.path.join(directory, fname)
        print(f"Generating {path}...")

        with open(path, 'wb') as f:
            # 1. Write the 'Header' (Total count of elements)
            # 'i' represents a standard 4-byte integer
            f.write(struct.pack('i', count_per_file))
            
            # 2. Generate and write the random integers
            # We write in chunks to be memory efficient
            chunk_size = 100000
            for _ in range(0, count_per_file, chunk_size):
                current_chunk = min(chunk_size, count_per_file - _)
                # Create a list of random ints
                data = [random.randint(-1000000, 1000000) for _ in range(current_chunk)]
                # Pack the entire list into binary format and write
                f.write(struct.pack(f'{current_chunk}i', *data))
        
        print(f"Finished {fname}")

if __name__ == "__main__":
    target_dir = "./files/"
    files = ["f1.bin", "f2.bin", "f3.bin", "f4.bin"]
    elements_per_file = 1000000  # 1 million integers per file
    
    generate_binary_dataset(target_dir, files, elements_per_file)
    print("\nAll files generated successfully.")