package DataTest;

import java.util.Date;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.AnnotationConfiguration;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import models.Data;


public class DataORMTest {
	private static SessionFactory sf;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		 sf = new AnnotationConfiguration().configure("hibernate.cfg.xml").buildSessionFactory();
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		sf.close();
	}

	@Test
	public void test() {
		Data data = new Data("temperature", new Date(), "33", "DHT11", "¡æ");
		Session session = sf.openSession();
		session.save(data);
		System.out.println(data.getId());
	}

}
