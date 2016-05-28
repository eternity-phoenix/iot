package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.util.Date;

import org.hibernate.Session;

import models.Data;

public class Process implements Runnable {
	private Socket socket;
	private Session session;
	
	public Process() {
	}	

	public Process(Socket socket, Session session) {
		super();
		this.socket = socket;
		this.session = session;
	}

	public Socket getSocket() {
		return socket;
	}

	public void setSocket(Socket socket) {
		this.socket = socket;
	}

	public Session getSession() {
		return session;
	}

	public void setSession(Session session) {
		this.session = session;
	}

	@Override
	public void run() {
		BufferedReader br = null;
		try {
			br = new BufferedReader(
					new InputStreamReader(this.socket.getInputStream(), "utf-8"));
			char read[] = new char[2048];
			br.read(read);
			String str = new String(read);
			String[] strs = str.split("|");
			for(int i = 0; i < strs.length; i++) {
				if(i == 1)
					break;
				String[] sd = strs[i].split("~");
				if(sd.length < 3)
					break;
				if(sd.length == 4)
					sd[3] = this.parse(sd[1], sd[3]);
				else if 
					break;
				Data data = new Data(sd[0], new Date(), sd[1], strs[0], sd[2]);
				session.save(data);	
			}
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if(br != null)
					br.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	private String parse(String value, String format) {
		byte bs[] = value.getBytes();
		int count = 0;
		for(int b : bs) {
			if(b < 0)
				b = 256 + b;
			count = count * (int) Math.pow(2, 8) + b;
		}
		return count + "";
	}
}
