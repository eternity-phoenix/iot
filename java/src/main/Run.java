package main;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.UnknownHostException;

import org.hibernate.SessionFactory;
import org.hibernate.cfg.AnnotationConfiguration;

import server.Process;

public class Run {
	public static void main(String[] args) throws UnknownHostException, IOException {
		ServerSocket serverSocket = new ServerSocket(8080);
		SessionFactory sf = new AnnotationConfiguration().configure("hibernate.cfg.xml").buildSessionFactory();
		while(true) {
			new Thread(new Process(serverSocket.accept(), sf.openSession())).start();
		}
	}
}
