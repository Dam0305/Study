package stack;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

//스택 클래스
public class Stack {
	private int top;
	private int maxSize;
	private int data[];

	public Stack() {
		top = -1;
		maxSize = 10000;
		data = new int[this.maxSize];
	}

  //is_Empty
	public int empty() {
		if (top == -1) {
			return 1;
		} else {
			return 0;
		}
	}

  //삽입
	public void push(int x) {
		data[++top] = x;

	}

  //삭제
	public int pop() {
		if (empty() == 1) {
			return -1;
		} else {
			return data[top--];
		}
	}

  //크기 반환
	public int size() {
		return top + 1;
	}

  //peek
	public int top() {
		if (empty() == 1) {
			return -1;
		} else {
			return data[top];
		}
	}

	public static void main(String args[]) throws IOException {
		int cnt;
		int data;
		String temp;
		String order[];
		Stack s = new Stack();

		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));

		cnt = Integer.parseInt(bf.readLine());

		while (cnt != 0) {
			temp = bf.readLine();
			order = temp.split(" ");

			switch (order[0]) {
			case "push":
				data = Integer.parseInt(order[1]);
				s.push(data);
				break;

			case "pop":
				System.out.println(s.pop());
				break;

			case "size":
				System.out.println(s.size());
				break;

			case "empty":
				System.out.println(s.empty());
				break;

			case "top":
				System.out.println(s.top());
				break;
			}
			cnt--;
		}
	}
}
