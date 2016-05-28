package DataTest;

import static org.junit.Assert.*;

import java.math.BigInteger;
import java.util.Arrays;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

public class TmpTest {

	@Test
	public void test() {
		String  str = "123456D0ºÃ¡æ";
		byte[] bs = str.getBytes();
		
		System.out.println(new BigInteger(1, bs).toString(2));
		//System.out.println(new BigInteger(-1, bs).toString(2));
		//System.out.println(new BigInteger(0, bs).toString(2));
		for(byte b : bs) {
			System.out.println((int) (b));
		}
		System.out.println(Arrays.toString(bs));
		
		char[] cs = str.toCharArray();
		System.out.println(Arrays.toString(cs));
		
		
		System.out.println(2^8);
		System.out.println((int) Math.pow(2, 8));
		byte bb = (byte) 0b1111_1111;
		System.out.println(bb);
	}

}
