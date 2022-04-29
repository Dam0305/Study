package linkedList;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

//노드
class Node {
	private int data;
	public Node next;

	public Node(int data) {
		this.data = data;
		this.next = null;
	}

	public Node(int data, Node next) {
		this.data = data;
		this.next = next;
	}

	public int getData() {
		return this.data;
	}
}

//연결리스트 클래스
public class LinkedList {
	private Node head;

	public LinkedList() {
		head = null;
	}
  
  //삽입
  public void insertNode(int data, Node pre) {
		Node newNode = new Node(data);
		newNode.next = pre.next;
		pre.next = newNode;

	}

  //마지막에 삽입
	public void insertLastNode(int data) {
		Node newNode = new Node(data);
		
    if (head == null) {
			this.head = newNode;
		}
    else {
			Node temp = head;
			
      while (temp.next != null) {
				temp = temp.next;
			}
			temp.next = newNode;
		}
	}

  //처음에 삽입
	public void insertFirstNode(int data) {
		Node newNode = new Node(data);
		
    if (head == null) {
			this.head = newNode;
		}
    else {
			newNode.next = head;
			head = newNode;
		}
	}

  //검색
	public Node serchNode(int data) {
		Node temp = this.head;
		
    while (temp != null) {
			if (data == temp.getData()) {
				return temp;
			}
      else {
				temp = temp.next;
			}
		}
		return temp;
	}

  //리스트 뒤집기
	public void reverse() {
		Node next = head;
		Node current = null;
		Node pre = null;

		while (next != null) {
			pre = current;
			current = next;
			next = next.next;
			current.next = pre;
		}
		head = current;
	}
  
  //리스트 출력
	public void printList() {
		Node temp = head;
		
    while (temp != null) {
			System.out.printf("%d -> ", temp.getData());
			temp = temp.next;
		}
		System.out.println();
	}

  //노드 삭제
	public void deleteNode() {
		Node temp, pre;

		if (head == null) {
			return;
		}
		if (head.next == null) {
			head = null;
		}
    else {
			pre = head;
			temp = head.next;
			
      while (temp.next != null) {
				pre = temp;
				temp = temp.next;
			}
			pre.next = null;
		}
	}

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		int order, data;
		LinkedList list = new LinkedList();
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));

		while (true) {
      
			System.out.println("1. 첫번째에 노드 삽입");
			System.out.println("2. 마지막에 노드 삽입");
			System.out.println("3.       노드 뒤집기");
			System.out.println("4.   마지막 노드 삭제");
			System.out.println("5.            종료");
			order = Integer.parseInt(bf.readLine());
      
			switch (order) {
			case 1:
				System.out.println("데이터를 입력해주세요");
				data = Integer.parseInt(bf.readLine());
				list.insertFirstNode(data);
				list.printList();
				break;
          
			case 2:
				System.out.println("데이터를 입력해주세요");
				data = Integer.parseInt(bf.readLine());
				list.insertLastNode(data);
				list.printList();
				break;
          
			case 3:
				list.reverse();
				list.printList();
				break;
          
			case 4:
				list.deleteNode();
				list.printList();
				break;
          
			case 5:
				System.exit(0);
			}
		}
	}

	
}

