#pragma once
// QPC로부터 시계 주파수(초당 틱 수)를 가져옴

double getFrequency();

// 현재 QPC 틱 수를 반환
LARGE_INTEGER now();