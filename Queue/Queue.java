package queue;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

//클래스 생성
public class Queue {

	private int data[];
	private int front, rear;
	private int maxSize;

	public Queue() {
		this.front = -1;
		this.rear = -1;
		maxSize = 10000;
		this.data = new int[this.maxSize];
	}

  //is_Empty
	public boolean isEmpty(Queue Q) {
		if (Q.front == Q.rear) {
			return true;
		} else
			return false;
	}

  //is_Full
	public boolean isFull(Queue Q) {
		if (Q.rear == (maxSize - 1)) {
			return true;
		} else
			return false;
	}

  //삽입
	public void enQueue(Queue Q, int data) {
		if (isFull(Q)) {
			System.out.println("Queue is full!");
			System.exit(0);
		} else {
			Q.rear++;
			Q.data[Q.rear] = data;
		}
	}

  //삭제
	public int deQueue(Queue Q) {
		if (isEmpty(Q)) {
			return -1;
		} else {
			Q.front++;
			return Q.data[Q.front];
		}
	}

  //크기 반환
	public int size(Queue Q) {
		if (isEmpty(Q)) {
			return 0;
		} else {
			return Q.rear - Q.front;
		}
	}

  //맨 앞에 있는 원소 확인
	public int front(Queue Q) {
		if (isEmpty(Q)) {
			return -1;
		} else {
			return Q.data[Q.front + 1];
		}
	}

  //맨 뒤에 있는 원소 확인
	public int back(Queue Q) {
		if (isEmpty(Q)) {
			return -1;
		} else {
			return Q.data[Q.rear];
		}
	}

	public static void main(String args[]) throws IOException {

		Queue Q = new Queue();
		int cnt, data;
		String temp;
		String order[];
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

		cnt = Integer.parseInt(bf.readLine());

		while (cnt != 0) {
			temp = bf.readLine();
			order = temp.split(" ");

			switch (order[0]) {
			case "push":
				data = Integer.parseInt(order[1]);
				Q.enQueue(Q, data);
				break;
          
			case "pop":
				writer.write(Integer.toString(Q.deQueue(Q)));
				writer.newLine();
				writer.flush();
				break;
          
			case "size":
				writer.write(Integer.toString(Q.size(Q)));
				writer.newLine();
				writer.flush();
				break;
          
			case "front":
				writer.write(Integer.toString(Q.front(Q)));
				writer.newLine();
				writer.flush();
				break;
          
			case "back":
				writer.write(Integer.toString(Q.back(Q)));
				writer.newLine();
				writer.flush();
				break;
          
			case "empty":
				if (Q.isEmpty(Q)) {
					writer.write(Integer.toString(1));
					writer.newLine();
					writer.flush();
				} else {
					writer.write(Integer.toString(0));
					writer.newLine();
					writer.flush();
				}
				break;
			}
			cnt--;
		}
		bf.close();
		writer.close();
	}
}
