package models;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;


@Entity
public class Data {
	private Integer id;
	private String attribute;
	private Date created_at;
	private String value;
	private String sensor_id;
	private String unit;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	@Column(length=50)
	public String getAttribute() {
		return attribute;
	}
	public void setAttribute(String attribute) {
		this.attribute = attribute;
	}
	@Temporal(TemporalType.TIMESTAMP)
	public Date getCreated_at() {
		return created_at;
	}
	public void setCreated_at(Date created_at) {
		this.created_at = created_at;
	}
	@Column(length=1000)
	public String getValue() {
		return value;
	}
	public void setValue(String value) {
		this.value = value;
	}
	@Column(length=50)
	public String getSensor_id() {
		return sensor_id;
	}
	public void setSensor_id(String sensor_id) {
		this.sensor_id = sensor_id;
	}
	@Column(length=50)
	public String getUnit() {
		return unit;
	}
	public void setUnit(String unit) {
		this.unit = unit;
	}
	
	public Data() {
	}
	public Data(String attribute, Date created_at, String value, String sensor_id, String unit) {
		super();
		this.attribute = attribute;
		this.created_at = created_at;
		this.value = value;
		this.sensor_id = sensor_id;
		this.unit = unit;
	}
	
	
}
