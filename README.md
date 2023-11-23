<div align="justify">
<h2>EV Embedded System</h2>

**2023 대학생 스마트 e모빌리티 경진대회 EV부문** 출전을 위해 아래 시스템을 개발했습니다. <br/>
- **속도계 및 계기판 시스템**
- **차량 데이터 로거** <br/>
</div>


<p align="center">
  <br>
  <img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/902a839e-314e-43a7-b9ae-bb464a381d6a" width="500" height="400"> <img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/b9375fed-87d7-40e7-8d77-7916480a3057" width="300" height="400">
  <br>
</p>

## 목차
  - [개요](#개요) 
  - [구현 기능](#구현-기능)
  - [보완할 점](#보완할-점)

<br>

## 개요
- 프로젝트 지속기간: 2023.01-2023.10 (10개월)
- 개발 언어 및 기술: C/C++
- 팀 규모: **30인 1팀** ***(개발 5인 1팀)***

### 수상
● 🥉**장려상** - 2023 대학생 스마트 e모빌리티 경진대회 EV부문

<br>

## 구현 기능

### 1. 속도계 및 계기판 시스템
본 대회 규정 중 감속구간에 대한 감점을 피하기 위해 속도계를 제작하였다. 속도계의 목표는 다음과 같다.
- 70km/h까지 속도를 측정할 수 있어야 한다.
- 속도를 정확하게 측정해야 한다.
- 제한 속도 이상과 이하일 때 드라이버가 쉽게 이를 인지할 수 있어야 한다.
<br/>

**측정 방식**

속도계는 아래 그림과 같이 휠 디스크에 광센서를 달아 측정 시스템을 구축하였다.
<p align="center">
<img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/2e535e35-a1b1-446f-9aa7-7cd53ab80cc4">
</p>
측정 방식은 펄스와 펄스 사이의 시간을 측정하는 방식인 T 방식을 채택했다. T 방식은 저속 rpm 측정 방식이며, 최고 rpm이 867인 우리 차량에 적합한 방식이다. 수식은 다음과 같다.
<p align="center">
<img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/81acc8fe-9e63-4dcc-aff9-b2f2b5021bf4">
</p>

**계기판**<br/>
속도를 출력하는 디스플레이는 I2C통신 방식 2.42인치 OLED를 사용하였다. OLED는 디자인 옵션이 풍부하기 때문에 차량의 속도에 대한 정보를 시각적으로 전달할 수 있다. 우리는 제한 속도 이상일 때 속도와 배경의 색을 반전시키는 방법을 통해 드라이버가 이를 쉽게 인지할 수 있도록 하였다. 아래 그림은 제한 속도를 50km/h로 설정했을 때이다.
<p align="center">
<img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/ddef8017-898a-4a5b-8e29-963a8c626203"> <img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/4aa1cb4a-b7ce-488a-b33f-90b624a1c595">
</p>
<br>

**블록 다이어그램**<br/><br/>
![image](https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/888d9da5-cb7b-4737-83ca-4b918df96a55)

<br>

### 2. 데이터 로깅 및 차량 성능 프로파일
속도를 컨트롤러와 속도계 등의 데이터를 디스플레이에 표시하는 것에 그치지 않고, 데이터 로깅을 통해 주행 데이터를 엑셀로 저장하고 지속해서 문제해결을 할 수 있도록 하였다.<br/><br/>

**Controller CAN Protocol**<br/>
차량 속도 뿐 아니라 차량 상태 특히, EV에서 중요한 부분인 모터와 배터리 관련 데이터를 로깅하기 위해 Controller의 CAN Protocol을 조사했다. 아래와 같이 데이터가 명시되어 있었다.
<p align="center">
<img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/cac7b984-4d0f-4c13-b94c-f2049a52b8bd">
</p>

초록색으로 표시된 데이터 목록 중, **배터리 전압, 모터 전류, 쓰로틀, 컨트롤러/모터 온도**를 로깅에 포함하기로 결정했다.

위의 데이터를 추가적으로 로깅하기 위해 **MCP2515** 모듈을 이용해 CAN 통신 신호를 SPI 통신으로 데이터를 수신했다. 250kbps CAN bus 속도에서 50ms 주기로 Controller 데이터와 Motor 데이터를 수신하였다.

아래 사진은 수신한 데이터 중 일부를 보여주고, 그래프는 시간에 따른 모터 온도의 변화를 시각화한 것이다. 약 600m의 경기장을 16~18바퀴 주행했을 당시 실제 모터 온도의 변화를 확인할 수 있다.
<p align="center">
<img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/1f6f87d0-04c3-47aa-a7a3-118a9181ba1f" width="230" height="300"> <img src="https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/616e49d7-95bd-4b00-a5a9-e502abf75234" width="500" height="300">
</p>
<br>

**블록 다이어그램**<br/><br/>
![image](https://github.com/HarrysK99/Vehicle-Embedded-System/assets/81846798/c72e8a6b-2bb4-4b76-a910-7831e54c57ff)

<br>

## 보완할 점
- [ ] (속도계) 슬립 감지 기능 추가
- [ ] (속도계) 토크 센서와 함께 토크벡터링 기능 구현해보기
- [ ] (데이터로거) 랩 자동 갱신 기능 추가

</p>

<br>

## 라이센스

MIT &copy; [NoHack](mailto:lbjp114@gmail.com)
