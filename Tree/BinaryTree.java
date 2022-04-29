package tree;

import java.util.Scanner;

/*
 * 이진트리
 * 				15
 * 			 /		\
 * 		   7		10
 * 		 /		  /		\
 * 	   31		25		16
 *	  /			  \
 *	 4			   13
 */


//노드
class treeNode {
	int data;
	treeNode left;
	treeNode right;
}

//이진트리
public class BinaryTree {

	private treeNode root;

	public treeNode init(treeNode l, int data, treeNode r) {
		treeNode root = new treeNode();
		root.data = data;
		root.left = l;
		root.right = r;

		return root;
	}

  //전위순회
	public void preorder(treeNode root) {
		if (root != null) {
			System.out.printf("%d ", root.data);
			preorder(root.left);
			preorder(root.right);
		}
	}

  //중위순회
	public void inorder(treeNode root) {
		if (root != null) {
			inorder(root.left);
			System.out.printf("%d ", root.data);
			inorder(root.right);
		}
	}

  //후위순회
	public void postorder(treeNode root) {
		if (root != null) {
			postorder(root.left);
			postorder(root.right);
			System.out.printf("%d ", root.data);
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BinaryTree tree = new BinaryTree();

    //노드 연결
		treeNode n7 = tree.init(null, 13, null);
		treeNode n6 = tree.init(null, 4, null);
		treeNode n5 = tree.init(n6, 31, null);
		treeNode n4 = tree.init(n5, 7, null);
		treeNode n3 = tree.init(null, 25, n7);
		treeNode n2 = tree.init(null, 16, null);
		treeNode n1 = tree.init(n3, 10, n2);
		treeNode n0 = tree.init(n4, 15, n1);

		Scanner in = new Scanner(System.in);

		int order;

		while (true) {
			System.out.println("1. preorder");
			System.out.println("2. inorder");
			System.out.println("3. postorder");
			System.out.println("4. exit");

			order = in.nextInt();

			switch (order) {
			case 1:
				System.out.println("preorder");
				tree.preorder(n0);
				System.out.println();
				break;
          
			case 2:
				System.out.println("inorder");
				tree.inorder(n0);
				System.out.println();
				break;
          
			case 3:
				System.out.println("postorder");
				tree.postorder(n0);
				System.out.println();
				break;
          
			case 4:
				System.out.println("good bye");
				System.exit(0);
				break;
			}
		}

	}

}
