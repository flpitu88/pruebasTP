#include "shared_strs.h"

char* id_a_mensaje(int id) {
	switch (id) {
	case CAMBIO_CRITERIO: {
		return "CAMBIO_CRITERIO";
	}
	case HANDSHAKE_PERSONAJE_ORQUESTADOR: {
		return "HANDSHAKE_PERSONAJE_ORQUESTADOR";
	}
	case UBICACION_CAJA: {
		return "UBICACION_CAJA";
	}
	case MUERTE_PERSONAJE: {
		return "MUERTE_PERSONAJE";
	}
	case MOVIMIENTO_PERMITIDO: {
		return "MOVIMIENTO_PERMITIDO";
	}
	case MUERTE_CORRECTA: {
		return "MUERTE_CORRECTA";
	}
	case HANDSHAKE_NIVEL_ORQUESTADOR: {
		return "HANDSHAKE_NIVEL_ORQUESTADOR";
	}
	case RECURSOS_LIBERADOS: {
		return "RECURSOS_LIBERADOS";
	}
	case DETECCION_DEADLOCK: {
		return "DETECCION_DEADLOCK";
	}
	case MUERTE_ANORMAL: {
		return "MUERTE_ANORMAL";
	}
	case BLOQUEO_PERSONAJE: {
		return "BLOQUEO_PERSONAJE";
	}
	case INICIALIZAR_PERSONAJE: {
		return "INICIALIZAR_PERSONAJE";
	}
	case PERSONAJE_LIBERADO: {
		return "PERSONAJE_LIBERADO";
	}
	case CAJA_FUERA_DE_LIMITE: {
		return "CAJA_FUERA_DE_LIMITE";
	}
	case PERSONAJE_NO_LIBERADO: {
		return "PERSONAJE_NO_LIBERADO";
	}
	case PEDIR_RECURSO: {
		return "PEDIR_RECURSO";
	}
	case SIN_RECURSOS: {
		return "SIN_RECURSOS";
	}
	case CON_RECURSOS: {
		return "CON_RECURSOS";
	}
	case AVISO_MOVIMIENTO: {
		return "AVISO_MOVIMIENTO";
	}
	case FINALIZAR: {
		return "FINALIZAR";
	}
	case MOVIMIENTO_EXITO: {
		return "MOVIMIENTO_EXITO";
	}
	case MUERTE_ALCANCE_ENEMIGO: {
		return "MUERTE_ALCANCE_ENEMIGO";
	}
	case MUERTE_POR_DEADLOCK: {
		return "MUERTE_POR_DEADLOCK";
	}
	case CONTINUA_NIVEL: {
		return "CONTINUA_NIVEL";
	}
	case TERMINA_NIVEL: {
		return "TERMINA_NIVEL";
	}
	case ME_QUEDE_SIN_VIDAS: {
		return "ME_QUEDE_SIN_VIDAS";
	}
	default: {
		return "DESCONOCIDOOOO(?)";
	}

	}
}
