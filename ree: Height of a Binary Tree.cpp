int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct node* root) {
    if (root == NULL) {
        return -1;
    } else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        return 1 + max(leftHeight, rightHeight);
    }
}
