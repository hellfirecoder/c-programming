def bubble_sort(arr):
   
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def cocktail_shaker_sort(arr):
    n = len(arr)
    swapped = True
    start = 0
    end = n - 1
    while swapped:
        swapped = False

        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True

        if not swapped:
            break

        swapped = False
        end = end - 1

        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        
        start = start + 1
    return arr

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def main():
    try:
        input_str = input("Enter a list of numbers separated by spaces: ")
        original_list = [int(item) for item in input_str.split()]
    except ValueError:
        print("Invalid input. Please enter only numbers separated by spaces.")
        return

    while True:
        data_to_sort = original_list[:] 

        print("1. Bubble Sort")
        print("2. Cocktail Shaker Sort")
        print("3. Insertion Sort")
        print("4. Selection Sort")
        print("5. Exit")
        
        choice = input("Enter your choice (1-5): ")

        if choice in ['1', '2', '3', '4']:
            print(f"\nOriginal list: {data_to_sort}")

        if choice == '1':
            sorted_list = bubble_sort(data_to_sort)
            print(f"List after Bubble Sort: {sorted_list}")
        elif choice == '2':
            sorted_list = cocktail_shaker_sort(data_to_sort)
            print(f"List after Cocktail Shaker Sort: {sorted_list}")
        elif choice == '3':
            sorted_list = insertion_sort(data_to_sort)
            print(f"List after Insertion Sort: {sorted_list}")
        elif choice == '4':
            sorted_list = selection_sort(data_to_sort)
            print(f"List after Selection Sort: {sorted_list}")
        elif choice == '5':
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 5.")

if __name__ == "__main__":
    main()
