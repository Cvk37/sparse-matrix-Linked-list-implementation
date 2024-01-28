#include <iostream>
#include <vector>

struct Node {
    int row, col, val;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), val(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    std::vector<Node*> rows_head;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), rows_head(r, nullptr) {}

    void insert(int row, int col, int val) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Invalid row or column index." << std::endl;
            return;
        }

        if (val != 0) {
            Node* newNode = new Node(row, col, val);
            newNode->next = rows_head[row];
            rows_head[row] = newNode;
        }
    }

    bool isSparseMatrix() {
        int nonZeroCount = 0;

        for (int i = 0; i < rows; i++) {
            Node* current = rows_head[i];
            while (current != nullptr) {
                nonZeroCount++;
                current = current->next;
            }
        }

        return nonZeroCount <= (rows * cols) / 2;
    }

    void printLinkedListRepresentation() {
    for (int i = 0; i < rows; i++) {
        Node* current = rows_head[i];

        // Skip rows with no non-zero elements
        if (current == nullptr) {
            continue;
        }

        while (current != nullptr) {
            std::cout << "(" << current->row << ", " << current->col << ", " << current->val << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}


    ~SparseMatrix() {
        for (int i = 0; i < rows; i++) {
            Node* current = rows_head[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    SparseMatrix sparseMat(rows, cols);

    std::cout << "Enter the elements of the matrix:" << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int element;
            std::cout << "Element at position (" << i << ", " << j << "): ";
            std::cin >> element;
            sparseMat.insert(i, j, element);
        }
    }

    if (sparseMat.isSparseMatrix()) {
        std::cout << "The matrix is sparse." << std::endl;
        std::cout << "Linked List Representation:" << std::endl;
        sparseMat.printLinkedListRepresentation();
    } else {
        std::cout << "The matrix is not sparse." << std::endl;
    }

    return 0;
}

