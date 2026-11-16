const byte SENSOR_PIN = 2;          // пин, к которому подключен OUT датчика FC-33
const int SLOTS = 20;               // количество прорезей (щелей) на диске

// Считаем ФРОНТЫ сигнала (переходы LOW->HIGH), 
// поэтому один прорез = 1 импульс на один проход.
const float DEGREES_PER_SLOT = 360.0 / SLOTS;  // градусов на один импульс

volatile long pulseCount = 0;       // счётчик импульсов (volatile — изменяется в прерывании)
float totalDegrees = 0;             // суммарный угол с учётом направления

// ============ Функция прерывания =============
// Срабатывает при переходе сигнала от LOW к HIGH (прорезь прошла мимо сенсора).
void sensorISR() {
  pulseCount++;
}

// ============== Инициализация ================
void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_PULLUP);   // подтяжка — нужен, т.к. выход датчика с открытым коллектором
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorISR, RISING);
  Serial.println("FC-33: измерение угла поворота колеса");
  Serial.print("Градусов на один импульс: ");
  Serial.println(DEGREES_PER_SLOT);
}

// ================= Главный цикл ==============
void loop() {
  // Копируем счётчик, чтобы прерывание не поменяло его во время чтения
  noInterrupts();
  long count = pulseCount;
  interrupts();

  // Переводим количество импульсов в градусы
  totalDegrees = count * DEGREES_PER_SLOT;

  // Нормализуем угол в диапазон 0..360 (без накопления)
  float angle = fmod(totalDegrees, 360.0);
  if (angle < 0) angle += 360.0;

  // Выводим результат
  Serial.print("Импульсов: ");
  Serial.print(count);
  Serial.print(" | Полных оборотов: ");
  Serial.print(totalDegrees / 360.0, 3);
  Serial.print(" | Угол: ");
  Serial.print(angle, 1);
  Serial.println("°");

  delay(200);   // обновление ~5 раз в секунду
}
